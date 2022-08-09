#include "usb_names.h"

#define MIDI_NAME   {'R','o','c','k','S','t','o','r','m','e','r'}
#define MIDI_NAME_LEN  11

#define MANUFACTURER_NAME  {'z','1','o','d'}
#define MANUFACTURER_NAME_LEN 4

struct usb_string_descriptor_struct usb_string_product_name = {
  2 + MIDI_NAME_LEN * 2,
  3,
  MIDI_NAME
};

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
  2 + MANUFACTURER_NAME_LEN * 2,
  3,
  MANUFACTURER_NAME
};
