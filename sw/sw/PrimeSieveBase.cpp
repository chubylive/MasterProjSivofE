#include "PrimeSieveBase.h"

PrimeSieveBase::PrimeSieveBase() : NUMBER_OF_PE(280),
                                   NUMBER_OF_ROWS(512)
{
    FIRST_PRIME = 2;
    MAX_OFFSET = ((NUMBER_OF_ROWS << 5) - 1);
    MAX_N = (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1);
    device_base_vaddress[0] = (unsigned *)getvaddr(BASE_ADDRESS_0);
    device_base_vaddress[1] = (unsigned *)getvaddr(BASE_ADDRESS_1);
    NUMBER_OF_STATUS_REGISTERS = ((NUMBER_OF_PE / 32) + (((NUMBER_OF_PE % 32) == 0) ? 0 : 1));
    delta[0] = 4;
    delta[1] = 2;
}

PrimeSieveBase::~PrimeSieveBase()
{
}

void *PrimeSieveBase::getvaddr(off_t phys_addr)
{
    void *mapped_base;
    int memfd;

    void *mapped_dev_base;
    off_t dev_base = phys_addr;

    memfd = open("/dev/mem", O_RDWR | O_SYNC); // to open this the program needs to be run as root
    if (memfd == -1)
    {
        printf("Can’t open /dev/mem.\n");
        exit(0);
    }

    // Map one page of memory into user space such that the device is in that page, but it may not
    // be at the start of the page

    mapped_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & (~MAP_MASK));
    if (mapped_base == (void *)-1)
    {
        printf("Can’t map the memory to user space.\n");
        exit(0);
    }

    // get the address of the device in user space which will be an offset from the base
    // that was mapped as memory is mapped at the start of a page

    mapped_dev_base = (void *)(((off_t)mapped_base) + (off_t)(dev_base & MAP_MASK));
    return mapped_dev_base;
}

unsigned *PrimeSieveBase::pe_command_register_vaddress(unsigned pe_id, unsigned register_id)
{
    unsigned *vaddress;
    if (pe_id < 128)
    {
        vaddress = device_base_vaddress[0] + (pe_id << 1) + register_id;
    }
    else
    {
        vaddress = device_base_vaddress[1] + ((pe_id - 128) << 1) + register_id;
    }
    return vaddress;
}

unsigned *PrimeSieveBase::pe_data_register_vaddress(unsigned pe_id)
{
    unsigned *vaddress;
    if (pe_id < 128)
    {
        vaddress = device_base_vaddress[0] + 320 + pe_id;
    }
    else
    {
        vaddress = device_base_vaddress[1] + 320 + (pe_id - 128);
    }
    return vaddress;
}

unsigned *PrimeSieveBase::pe_status_register_vaddress(unsigned pe_id)
{
    unsigned *vaddress;
    if (pe_id < 128)
    {
        vaddress = device_base_vaddress[0] + 480 + (pe_id >> 5);
    }
    else
    {
        vaddress = device_base_vaddress[1] + 480 + ((pe_id - 128) >> 5);
    }
    return vaddress;
}

void PrimeSieveBase::write_command_register_0(unsigned pe_id, unsigned argument_2, unsigned argument_3)
{
    unsigned *vaddress = pe_command_register_vaddress(pe_id, 0);
    *vaddress = argument_2 | (argument_3 << 16);
}

void PrimeSieveBase::write_command_register_1(unsigned pe_id, unsigned command, unsigned argument_1)
{
    unsigned *vaddress = pe_command_register_vaddress(pe_id, 1);
    *vaddress = command | (argument_1 << 4);
}

unsigned PrimeSieveBase::read_command_register(unsigned pe_id, unsigned register_id)
{
    unsigned *vaddress = pe_command_register_vaddress(pe_id, register_id);
    unsigned register_read_data = *vaddress;
    return register_read_data;
}

unsigned PrimeSieveBase::read_data_register(unsigned pe_id)
{
    unsigned *vaddress = pe_data_register_vaddress(pe_id);
    unsigned register_read_data = *vaddress;
    return register_read_data;
}

unsigned PrimeSieveBase::read_status_register(unsigned pe_id)
{
    unsigned *vaddress = pe_status_register_vaddress(pe_id);
    unsigned register_read_data = *vaddress;
    return register_read_data;
}

void PrimeSieveBase::clear_memory(unsigned pe_id)
{
    write_command_register_1(pe_id, PE_CLEAR_MEMORY_COMMAND);
}

void PrimeSieveBase::clear_memory_all()
{
    unsigned status_register[9];
    unsigned done;

    for (unsigned i = 0; i < 9; i++)
    {
        status_register[i] = 0;
    }

    for (unsigned pe_id = 0; pe_id < 280; pe_id++)
    {
        clear_memory(pe_id);
        status_register[pe_id >> 5] |= (1 << (pe_id & 31));
    }

    do
    {
        done = 1;
        for (unsigned i = 0; i < 9; i++)
        {
            if (status_register[i] != 0)
            {
                unsigned status = read_status_register(i << 5);
                if (status != 0)
                {
                    done = 0;
                }
                status_register[i] &= status;
            }
        }
    } while (done == 0);
}

unsigned PrimeSieveBase::read_memory_row(unsigned pe_id, unsigned row)
{
    unsigned status_register;
    unsigned data_register;

    write_command_register_1(pe_id, PE_READ_MEMORY_COMMAND, row);

    do
    {
        status_register = read_status_register(pe_id);
    } while (status_register != 0);

    data_register = read_data_register(pe_id);

    return data_register;
}

float PrimeSieveBase::time_compute_0(uint32_t n, unsigned pe, unsigned rows)
{
    reconfig(pe, rows, n);

    clock_t start, end;
    clear_memory_all();

    start = clock();
    compute_all();
    end = clock();

    float cpu_time = ((float)(end - start)) * 1000 / CLOCKS_PER_SEC;
    return cpu_time;
}

float PrimeSieveBase::time_compute_1(uint32_t n, unsigned pe, unsigned rows)
{
    reconfig(pe, rows, n);

    unsigned *clock_counter_vaddress = device_base_vaddress[1] + 496;
    unsigned clockStart, clockEnd;
    clear_memory_all();

    clockStart = *clock_counter_vaddress;
    compute_all();
    clockEnd = *clock_counter_vaddress;

    float cpu_time = ((1 / 5e7) * ((float)clockEnd)) * 1000;
    return cpu_time;
}

void PrimeSieveBase::read_memory_all()
{
    for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id++)
    {
        read_memory(pe_id);
    }
}
