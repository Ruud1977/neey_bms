#pragma once

#include "esphome/components/ble_client/ble_client.h"
#include "esphome/core/component.h"

namespace esphome {
namespace neey_bms {

class NEEYBMS : public esphome::Component, public esphome::ble_client::BLEClientNode {
 public:
  void set_ble_client(esphome::ble_client::BLEClient *client) { this->parent_ = client; }
  void dump_config() override;
  void loop() override;

 protected:
  void on_ble_data(const std::vector<uint8_t> &data);
};

}  // namespace neey_bms
}  // namespace esphome
