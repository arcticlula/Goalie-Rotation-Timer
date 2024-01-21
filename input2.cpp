// #include <cstdint>

// #define NUM_OF_INPUTS 2

// typedef void (*handler)(void *arg);
// typedef void (*cb_handler)(Input *input);

// typedef struct {
//   void * arg;
//   handler fn;
// } closure_t;

// typedef struct {
//   void * arg;
//   cb_handler fn;
// } cb_closure_t;

// class ClickCount {
//     uint8_t click;
//     uint8_t hold;
//   public:
//     ClickCount() : click(0), hold(0) {}
//     uint8_t getClick() const { return click; }
//     uint8_t getHold() const { return hold; }
//     void incrementClick() { click++; }
//     void incrementHold() { hold++; }
// };

// class Input {
//     static uint8_t id;
//     gpio_num_t pin;
//     bool state;
//     bool level;
//     bool has_debounce;
//     ClickCount count;
//     uint64_t last_click_timestamp = 0;
//     uint32_t debounce_ms = 50;

//     void (*on_click)(Input *);
//     void (*on_dbl_click)(Input *);
//     void (*on_hold)(Input *);

//     // Static array for storing click handlers
//     static cb_closure_t cb_handlers[NUM_OF_INPUTS][5];

//     // Static array for storing timer handles
//     static esp_timer_handle_t timer_debounce_handles[NUM_OF_INPUTS];
//     static esp_timer_handle_t timer_general_handles[NUM_OF_INPUTS];

//     // Static array for storing timer arguments
//     static esp_timer_create_args_t timer_debounce_args[NUM_OF_INPUTS];
//     static esp_timer_create_args_t timer_general_args[NUM_OF_INPUTS];

//     // Static array for storing button indices
//     static int timer_indices[NUM_OF_INPUTS];

//     // Static array for storing IRQ handlers
//     static closure_t irq_handlers[NUM_OF_INPUTS];

//     // Static array for storing button handler indices
//     static uint8_t button_handler_index[NUM_OF_INPUTS];

//   public:
//     Input(gpio_num_t pin, bool level, bool has_debounce, uint32_t time_ms,
//           void (*on_click)(Input *), void (*on_hold)(Input *), void (*on_dbl_click)(Input *));
// };
