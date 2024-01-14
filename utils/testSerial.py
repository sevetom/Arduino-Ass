import serial
import time

def open_serial():
    global ser
    try:
        # Apre la comunicazione seriale con Arduino
        ser = serial.Serial('COM3', 9600, timeout=1)
        time.sleep(10)
        print("Comunicazione seriale aperta")
    except Exception as e:
        print(f"Errore: {e}")
        exit(1)

def send_receive_data():
    try:
        # Invia 10 interi ad Arduino
        for i in range(1, 11):
            data_to_send = 1
            ser.write(f"{data_to_send}\n".encode())
            time.sleep(0.5)
            print(f"Invio giro {i}")
        print("Dati inviati ad Arduino")
    except Exception as e:
        print(f"Errore: {e}")
        
def recive_data():
    try:
        # Leggi la risposta di Arduino
        for i in range(1, 11):
            data = ser.readline().decode("utf").rstrip("\n")
            print(f"Arduino ha inviato: {data}")
            time.sleep(1)
    except Exception as e:
        print(f"Errore: {e}")


if __name__ == "__main__":
    open_serial()
    send_receive_data()
    recive_data()
