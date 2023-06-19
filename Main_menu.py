import tkinter as tk
import tkinter.messagebox
import customtkinter as ctk
from PIL import ImageTk, Image
import os

#-----archivos-------
#carpeta principal
Carpeta_principal = os.path.dirname(__file__)
#carpeta para imagenes
Carpeta_Imagenes = os.path.join(Carpeta_principal, "imagenes")

#------------------customtk----------------
ctk.set_appearance_mode("system")
ctk.set_default_color_theme("green")



class Inicio:
    def __init__(self):
        #---------------------------self-------------------------
        self.root = ctk.CTk()
        self.root.title("UNON'T_Alpha_test")
        self.root.iconbitmap(os.path.join(Carpeta_Imagenes, "Unon't_Logo.ico"))
        self.root.geometry("600x600")

        #------------------------funciones de self---------------

        #la primera funcion es solo un testeo
        def salir():
            self.root.destroy()

        def antes_de_salir():
            respuesta = tk.messagebox.askquestion("Saliendo de UNON'T", "¿Estas seguro de salir?")
            if respuesta == "yes" :
                salir()

        #------------------------Controles de self---------------

        botonOut = ctk.CTkButton(master=self.root, text = "Salir de UNON'T", command= antes_de_salir)
        botonOut.place(relx=0.8, rely=0.9, anchor=tk.CENTER)

        logo= ctk.CTkImage(Image.open(os.path.join(Carpeta_Imagenes, "Unon't_Logo.png")), size= (250, 250))
        etiqueta = ctk.CTkLabel(master=self.root, image=logo, text=" ")

        etiqueta.pack(pady=15)

        ctk.CTkButton(self.root, text="Iniciar partida").pack(pady=10)


        self.root.mainloop()