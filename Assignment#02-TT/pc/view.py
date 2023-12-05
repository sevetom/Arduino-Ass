import tkinter as tk

class View:

    def __init__(self):
        self.root = tk.Tk()
        img = tk.PhotoImage(file='./img/arduino_icon.png')
        self.root.iconphoto(False, img)
        self.root.title("Dashboard")
        self.configure_main_window()
        self.frame_lable = tk.Frame(self.root)
        self.frame_lable.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)
        self.error_flashing = False
        self.error_flash_interval = 500
        
        self.car_washed = 0
        self.status = "OK"
        self.temperature = 0
        
        self.label_car = tk.Label(self.frame_lable, text="Car Washed\n"+str(self.car_washed), borderwidth=1, relief="solid")
        self.label_status = tk.Label(self.frame_lable, text="Status\n"+str("OK" if self.status == "OK" else "ERROR"), fg="white", bg="gray", borderwidth=5, relief="sunken")
        self.label_temp = tk.Label(self.frame_lable, text="Temperature\n"+str("N/D" if self.temperature == 0 else self.temperature)+"°C", borderwidth=1, relief="solid")
        
        for label in [self.label_car, self.label_status, self.label_temp]:
            label.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        self.frame_button = tk.Frame(self.root)
        self.frame_button.pack(side=tk.BOTTOM, fill=tk.X, padx=10, pady=10)
        
        self.button = tk.Button(self.frame_button, text="Maintenance done", command=self.on_click)
        self.button.config(state='disabled')
        self.button.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
        
    def set_data(self, car_washed, status, temperature):
        self.car_washed = car_washed
        self.status = status
        self.temperature = temperature
        self.update_labels()
        
    def configure_main_window(self):
        screen_width = self.root.winfo_screenwidth() * 2 // 9
        screen_height = self.root.winfo_screenheight() * 2 // 9
        x_position = int(screen_width + screen_width * 0.75)
        y_position = int(screen_height + screen_height * 0.75)
        self.root.geometry(f"{screen_width}x{screen_height}+{x_position}+{y_position}")
        self.root.resizable(False, False)
        self.root.protocol("WM_DELETE_WINDOW", exit)
    
    def update_labels(self):
        self.label_car.config(text="Car Washed\n"+str(self.car_washed))
        self.label_status.config(text="Status\n"+str("OK" if self.status == "OK" else "ERROR"), fg="white", bg="gray")
        self.label_temp.config(text="Temperature\n"+str("N/D" if self.temperature == 0 else self.temperature)+"°C")
        if self.status == "ERROR":
            self.button.config(state='normal')
            self.flash_label()
        
    def flash_label(self):
        if self.status == "ERROR":
            if self.error_flashing:
                self.label_status.config(fg="red", bg="white")
            else:
                self.label_status.config(fg="white", bg="red")
            self.error_flashing = not self.error_flashing
            self.root.after(self.error_flash_interval, self.flash_label)
        else:
            self.label_status.config(fg="white", bg="gray")
            
    def on_click(self):
        self.status = "OK"
        self.button.config(state='disabled')
        self.update_labels()

    def run(self):
        self.update_labels()
        self.root.mainloop()