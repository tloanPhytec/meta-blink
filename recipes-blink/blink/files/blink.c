#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

// Setup GPIO0_18
#define GPIO0_ADDR_START 0x000600000
#define GPIO0_ADDR_END 0x0006000FF
#define GPIO0_SIZE (GPIO0_ADDR_END - GPIO0_ADDR_START)
#define GPIO0_PORT (1 << 18)
#define GPIO_DATA_OFFSET   0x000000018
#define GPIO_DIR_OFFSET    0x000000010
#define GPIO_CLEAR_OFFSET  0x00000001C

void *gpioAddress;
unsigned int *gpio_setdataout_addr;
unsigned int *gpio_direction_addr;
unsigned int *gpio_cleardata_addr;

void delay(unsigned long ms)
{
    clock_t start_ticks = clock();
    unsigned long millis_ticks = CLOCKS_PER_SEC / 1000;
    while (clock() - start_ticks < ms * millis_ticks){}
}

int main()
{
    int fd = open("/dev/mem", O_RDWR);

    gpioAddress = mmap(0, GPIO0_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO0_ADDR_START);

    close(fd);

    gpio_setdataout_addr  = gpioAddress + GPIO_DATA_OFFSET;
    gpio_direction_addr   = gpioAddress + GPIO_DIR_OFFSET;
    gpio_cleardata_addr   = gpioAddress + GPIO_CLEAR_OFFSET;

    *gpio_direction_addr &= ~(GPIO0_PORT);

    while (1)
    {
        *gpio_setdataout_addr |= GPIO0_PORT;
        delay(1000);
        *gpio_cleardata_addr  |= GPIO0_PORT;
        delay(1000);
    }
}
