
# from google search: vs code tasks.json input com ports extension "Command Variable"
import serial.tools.list_ports
import sys


def list_com_ports():
    '''
    TODO Docstring for list_com_ports
    '''

    ports = serial.tools.list_ports.comports()
    if not ports:
        print("No COM ports found")
        sys.exit(1)
    for port in ports:
        # The extension will use each line as a selection option
        if port.vid and port.vid:
            print(port.device)
            # print(f"Description: {port.description}\tVID: 0x{port.vid:04x} PID: 0x{port.pid:04x}")


if __name__ == "__main__":
    list_com_ports()
