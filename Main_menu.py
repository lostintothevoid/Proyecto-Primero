import tkinter as tk
import customtkinter as ctk
from PIL import Image
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
        
        def ir_a_prejuego():
            # esta funcion cerrara el menu principal para posteriormente abrir la prejuego
            salir()
            Ventana_pre_juego = opciones_pre_juego()


        #------------------------Controles de self---------------

        botonOut = ctk.CTkButton(master=self.root, text = "Salir de UNON'T", command= antes_de_salir)
        botonOut.place(relx=0.8, rely=0.9, anchor=tk.CENTER)

        logo= ctk.CTkImage(Image.open(os.path.join(Carpeta_Imagenes, "Unon't_Logo.png")), size= (250, 250))
        etiqueta = ctk.CTkLabel(master=self.root, image=logo, text=" ")

        etiqueta.pack(pady=15)

        ctk.CTkButton(self.root, text="Iniciar partida", command=ir_a_prejuego).pack(pady=10)
        ctk.CTkButton(self.root, text="Opciones").pack(pady=10)


        self.root.mainloop()
#-----funciones extras------
class funciones:
    
    def ventana_jugadores_2(self):
        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")

    def ventana_jugadores_3(self):
        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")

    def ventana_jugadores_4(self):
        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")

    def salir(self):
        ventana = ctk.CTkToplevel()
        ventana.destroy()


    def backtoMainMenu(self):
        ventana = ctk.CTkToplevel()
        ventana.destroy()
        ventana_back = Inicio()

objeto_func = funciones()

#-------nueva ventana-------
class opciones_pre_juego:
    botones = {'2 jugadores': objeto_func.ventana_jugadores_2, '3 jugadores': objeto_func.ventana_jugadores_3, '4 jugadores': objeto_func.ventana_jugadores_4, 'volver al menu': objeto_func.backtoMainMenu,'salir del juego': objeto_func.salir}
    def __init__(self):
        #---------------------------self-------------------------
        self.root = ctk.CTk()
        self.root.title("Sala de jugadores.")

        cont = 0

        for texto_boton in self.botones:
            button = ctk.CTkButton(master=self.root, text= texto_boton, height=50, width=200, command= self.botones[texto_boton])

            button.grid(row=cont//2, column=cont%2, padx=5, pady=5)   
            cont += 1
            

        self.root.mainloop() 
