#include "neey_bms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace neey_bms {

static const char *const TAG = "neey_bms";

void NEEYBMS::dump_config() {
  ESP_LOGCONFIG(TAG, "NEEY BMS Component");
}

void NEEYBMS::loop() {
  // Nothing yet — parser komt hier later
}

void NEEYBMS::on_ble_data(const std::vector<uint8_t> &data) {
  ESP_LOGD(TAG, "Received %d bytes", data.size());
  // Hier komt straks jouw echte frame parser
}

}  // namespace neey_bms
}  // namespace esphome

