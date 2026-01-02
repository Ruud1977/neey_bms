import esphome.codegen as cg

# Register the C++ component with ESPHome
neey_bms_ns = cg.esphome_ns.namespace("neey_bms")
NeeyBms = neey_bms_ns.class_("NeeyBms", cg.Component)
