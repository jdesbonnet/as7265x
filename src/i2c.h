#include <stdint.h>

int i2c_init(const char *i2c_fname);
void i2c_close(int i2c_fd);
int i2c_register_write(int i2c_fd, uint8_t slave_addr, uint8_t reg, uint8_t data);
int i2c_register_read(int i2c_fd, uint8_t slave_addr, uint8_t reg, uint8_t *result);
