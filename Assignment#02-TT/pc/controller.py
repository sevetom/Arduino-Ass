import serial.tools.list_ports
class Controller:
    def __init__(self, view):
        self.serialInst = serial.Serial()
        self.portsList = []
        self.portVar = None
        self.status = "OK"
        self.temperature = 0
        self.car_washed = 0
        self.view = view

    def select_port(self):
        ports = serial.tools.list_ports.comports()
        for onePort in ports:
            full_port = str(onePort)
            if " " in str(onePort):
                onePort = str(onePort).split(" ")
                onePort = onePort[0]
            self.portsList.append(str(onePort))
            print(f"{self.portsList.index(str(onePort))} - {str(full_port)}")

        val = input("Select Port: ")
        self.portVar = self.portsList.pop(int(val))
        print(f"Selected Port: {self.portVar}")

        self.serialInst.baudrate = 9600
        self.serialInst.timeout = 1
        self.serialInst.port = self.portVar
        print("Opening Port")
        self.serialInst.open()

    def read_serial(self):
        while True:
            if self.status == "ERROR" and self.view.status == "OK":
                self.status = self.view.status
                self.send_resolved_satatus()
                continue
            if self.serialInst.in_waiting:
                packet = self.serialInst.readline()
                packetDecoded = packet.decode('utf').rstrip("\n")
                print(packetDecoded)
                if not packetDecoded or not packetDecoded.startswith("Packet: "):
                    continue
                if packetDecoded.startswith("Packet: Temperature: "):
                    self.temperature = float(packetDecoded.split(" ")[2])
                elif packetDecoded.startswith("Packet: Car Washed: "):
                    self.car_washed += 1
                elif packetDecoded.startswith("Packet: Error: "):
                    self.status = "ERROR"
                self.view.set_data(self.car_washed, self.status, self.temperature)

    def send_resolved_satatus(self):
        self.serialInst.write(f"1".encode())
        print(f"Packet: Status: {self.status} SEND")
