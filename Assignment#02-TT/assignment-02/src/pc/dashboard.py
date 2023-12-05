import threading
import controller as cn
import view as vw

'''
Pc dashboard made for an arduino car washing
Made by:
- tommaso.ceredi@studiop.unibo.it
- tommaso.severi2@studio.unibo.it 
'''
if __name__ == "__main__":
    view = vw.View()
    controller = cn.Controller(view)
    controller.select_port()
    t1 = threading.Thread(target=controller.read_serial)
    t1.start()
    view.run()