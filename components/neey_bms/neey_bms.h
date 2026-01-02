#include "esphome.h"

class NeeyBms : public Component, public esphome::ble_client::BLEClientNode {
 public:
  NeeyBms(esphome::ble_client::BLEClient *client) {
    this->client_ = client;
  }

  void setup() override {
    this->client_->register_for_notify(this, "FFE0", "FFE1");
  }

  void on_notify(uint16_t handle, const std::vector<uint8_t> &data) override {
    ESP_LOGD("neey", "Notify %d bytes: %s", data.size(), format_hex_pretty(data).c_str());

    if (data.size() < 10) return;

    uint8_t frame_type = data[4];

    if (frame_type == 0x02) {
      parse_cell_frame(data);
    }
  }

  void parse_cell_frame(const std::vector<uint8_t> &d) {
    auto read_float = [&](int offset) {
      uint32_t raw = (d[offset] << 24) | (d[offset+1] << 16) | (d[offset+2] << 8) | d[offset+3];
      float f;
      memcpy(&f, &raw, sizeof(float));
      return f;
    };

    ESP_LOGI("neey", "Cell 1: %.3f V", read_float(9));
    ESP_LOGI("neey", "Cell 2: %.3f V", read_float(13));
    ESP_LOGI("neey", "Cell 3: %.3f V", read_float(17));
    ESP_LOGI("neey", "Cell 4: %.3f V", read_float(21));
    ESP_LOGI("neey", "Cell 5: %.3f V", read_float(25));
    ESP_LOGI("neey", "Cell 6: %.3f V", read_float(29));
    ESP_LOGI("neey", "Cell 7: %.3f V", read_float(33));
    ESP_LOGI("neey", "Cell 8: %.3f V", read_float(37));
    ESP_LOGI("neey", "Cell 9: %.3f V", read_float(41));
    ESP_LOGI("neey", "Cell 10: %.3f V", read_float(45));
    ESP_LOGI("neey", "Cell 11: %.3f V", read_float(49));
    ESP_LOGI("neey", "Cell 12: %.3f V", read_float(53));
    ESP_LOGI("neey", "Cell 13: %.3f V", read_float(57));
    ESP_LOGI("neey", "Cell 14: %.3f V", read_float(61));
    ESP_LOGI("neey", "Cell 15: %.3f V", read_float(65));
    ESP_LOGI("neey", "Cell 16: %.3f V", read_float(69));

    ESP_LOGI("neey", "Total voltage: %.3f", read_float(201));
    ESP_LOGI("neey", "Avg cell voltage: %.3f", read_float(205));
    ESP_LOGI("neey", "Delta cell voltage: %.4f", read_float(209));

    ESP_LOGI("neey", "Max cell index: %d", d[213] + 1);
    ESP_LOGI("neey", "Min cell index: %d", d[214] + 1);
  }

 protected:
  esphome::ble_client::BLEClient *client_;
};
