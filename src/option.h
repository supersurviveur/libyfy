#ifndef OPTION_H
#define OPTION_H
#include <stdbool.h>

/// @brief Create an option type for the given type
/// @param T The type to create an option type for
#define CREATE_OPTION_TYPE(T) \
    typedef struct {          \
        T value;              \
        bool is_some;         \
    } Option_##T;

/// @brief The option type for the given type
#define Option(T) Option_##T

/// @brief Create a Some option
#define Some(T, V) ((Option(T)){.value = V, .is_some = true})

/// @brief Create a None option
#define None(T) ((Option(T)){.is_some = false})

/// @brief Check if the option is Some
#define is_some(o) (o.is_some)
/// @brief Check if the option is None
#define is_none(o) (!o.is_some)

/// @brief Unwrap the option
#define unwrap_option(o)             \
    ({                               \
        if (is_none(o)) {            \
            PANIC("Unwrap of None"); \
        }                            \
        o.value;                     \
    })

/// @brief Unwrap the option or return the default value
#define unwrap_option_or(o, default) (is_none(o) ? default : o.value)

#endif  // OPTION_H