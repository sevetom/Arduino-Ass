import threading
import controller as cn
import view as vw

if __name__ == "__main__":
    view = vw.View()
    controller = cn.Controller(view)
    controller.select_port()
    t1 = threading.Thread(target=controller.read_serial)
    t1.start()
    view.run()