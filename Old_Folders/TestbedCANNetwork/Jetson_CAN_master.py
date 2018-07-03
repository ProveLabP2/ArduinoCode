import serial
import can

wireless_port = serial.Serial("/dev/ttyTHS2", 1200)

can_port = can.interface.Bus(channel='can0', bustype='socketcan_native')
try:
    while True:
        s_val = wireless_port.read()
        t_val = wireless_port.read()
        b_val = wireless_port.read()

        s_msg = can.Message(arbitration_id=0x10, 
                            data=[s_val], extended_id=False)
        can_port.send(s_msg)
        t_msg = can.Message(arbitration_id=0x20,
                            data=[t_val], extended_id=False)
        can_port.send(t_msg)
        b_msg = can.Message(arbitration_id=0x30,
                            data=[b_val], extended_id=False)
        can_port.send(b_msg)
except:
    can_port.close()
    wireless_port.close()
