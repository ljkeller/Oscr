/*
 * Rotate a coin display continuously with mcpwm servo control
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"

static const char *TAG = "Coin Rotator Main";

#define SERVO_MIN_PULSEWIDTH_US 700  // Maximum CCW rotation
#define SERVO_MAX_PULSEWIDTH_US 2300 // Maximum CW rotation

#define SERVO_PULSE_GPIO 23                  // GPIO connected to signal line of servo
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000 // 1 MHz, 1 us per tick
#define SERVO_TIMEBASE_PERIOD 50000          // 50000 ticks, 50 ms per period

static inline uint32_t middle_pulsewidth_us()
{
    return (SERVO_MIN_PULSEWIDTH_US + SERVO_MAX_PULSEWIDTH_US) / 2;
}

static inline uint32_t step_through_duty_cycles(int step)
{
    return SERVO_MIN_PULSEWIDTH_US + (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) * step / 8;
}

void rotate_display(mcpwm_cmpr_handle_t comparator, bool is_clockwise)
{
    const uint32_t smooth_offset = 40;
    const uint32_t rotation_magnitude = is_clockwise ? middle_pulsewidth_us() + smooth_offset : SERVO_MIN_PULSEWIDTH_US + smooth_offset;
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, rotation_magnitude));
}

// Helper function to find suitable duty cycle for rotation
void step_through_pwms_testing_helper(mcpwm_cmpr_handle_t comparator)
{
    while (true)
    {
        ESP_LOGI(TAG, "Top of rotation loop");
        for (int step = 0; step < 30; step++)
        {
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, middle_pulsewidth_us() + 80 / 3 * step));
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Start main()");
    ESP_LOGI(TAG, "Create timer and operator");

    mcpwm_timer_handle_t timer = NULL;
    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    mcpwm_oper_handle_t oper = NULL;
    mcpwm_operator_config_t operator_config = {
        .group_id = 0,
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

    ESP_LOGI(TAG, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    ESP_LOGI(TAG, "Create comparator and generator from the operator");
    mcpwm_cmpr_handle_t comparator = NULL;
    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    mcpwm_gen_handle_t generator = NULL;
    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, middle_pulsewidth_us()));

    ESP_LOGI(TAG, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));

    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

    const bool is_clockwise = true;
    rotate_display(comparator, is_clockwise);
}
