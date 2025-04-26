#include "main.h"
#include "adxl345.h"

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    if (ADXL345_Init(&hi2c1) == INIT_SUCCESS)
    {
        while (1)
        {
            float x = ADXL345_getGValue(&hi2c1, X, SCALE_FACTOR_4G);
            float y = ADXL345_getGValue(&hi2c1, Y, SCALE_FACTOR_4G);
            float z = ADXL345_getGValue(&hi2c1, Z, SCALE_FACTOR_4G);

            HAL_Delay(100);
        }
    }
    else
    {
        // Initialization error
    }
}
