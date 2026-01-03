import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import ble_client
from esphome.const import CONF_ID

AUTO_LOAD = ["ble_client"]

neey_bms_ns = cg.esphome_ns.namespace("neey_bms")
NEEYBMS = neey_bms_ns.class_("NEEYBMS", cg.Component, ble_client.BLEClientNode)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(NEEYBMS),
    cv.Required("ble_client_id"): cv.use_id(ble_client.BLEClient)
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var)
    ble = yield cg.get_variable(config["ble_client_id"])
    cg.add(var.set_ble_client(ble))
