import tkinter as tk
import customtkinter as ctk
from PIL import Image
import os
import csv

#-----archivos-------
#carpeta principal
Carpeta_principal = os.path.dirname(__file__)
#carpeta para imagenes
Carpeta_Imagenes = os.path.join(Carpeta_principal, "imagenes")

#------------------customtk----------------
ctk.set_appearance_mode("system")
ctk.set_default_color_theme("blue")
#------------fuente----------

#fuente_witgets = ('', 16)

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

        logo= ctk.CTkImage(Image.open(os.path.join(Carpeta_Imagenes, "Unon't_Logo.png")), size= (350, 350))
        etiqueta = ctk.CTkLabel(master=self.root, image=logo, text=" ")

        etiqueta.pack(pady=5)

        ctk.CTkButton(self.root, text="Iniciar partida", command=ir_a_prejuego).pack(pady=10)
        #ctk.CTkButton(self.root, text="Opciones").pack(pady=10)


        self.root.mainloop()
#-----funciones extras------
class funciones:
    
    def ventana_jugadores_2(self):
        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")
        ventana.geometry("200x200")
        ventana.resizable(False, False)

        ctk.CTkLabel(ventana, text="Nombre de jugador", anchor="center").pack()
        self.entrada = ctk.CTkEntry(ventana)
        self.entrada.insert(0, "EJ: Pepe360")
        self.entrada.bind("<Button-1>", lambda e: self.entrada.delete(0, 'end'))
        self.entrada.pack()

        jugadores = []  # Declarar la lista fuera de la función entry_process()

        def entry_process():
            jugador = self.entrada.get()
            jugadores.append(jugador)
            cant_players = len(jugadores)
            self.cont_players.configure(text=f"jugadores registrados: {cant_players}")
            if len(jugadores) == 2:
                with open("jugadores.txt", "a") as file:
                    for nombre in jugadores:
                        file.write(nombre + "\n")
                ventana.destroy()
            self.entrada.delete(0, "end")




        ctk.CTkButton(ventana, command=entry_process, text="ingresar", anchor="center").pack(pady=10)

        self.cont_players = ctk.CTkLabel(ventana, text="jugadores registrados: 0")
        self.cont_players.pack()






    def ventana_jugadores_3(self):
        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")
        ventana.geometry("200x200")
        ventana.resizable(False, False)

        ctk.CTkLabel(ventana, text="Nombre de jugador", anchor="center").pack()
        self.entrada = ctk.CTkEntry(ventana)
        self.entrada.insert(0, "EJ: Pepe360")
        self.entrada.bind("<Button-1>", lambda e: self.entrada.delete(0, 'end'))
        self.entrada.pack()

        jugadores = []  # Declarar la lista fuera de la función entry_process()

        def entry_process():
            jugador = self.entrada.get()
            jugadores.append(jugador)
            cant_players = len(jugadores)
            self.cont_players.configure(text=f"jugadores registrados: {cant_players}")            
            if len(jugadores) == 3:
                with open("jugadores.txt", "a") as file:
                    for nombre in jugadores:
                        file.write(nombre + "\n")
                ventana.destroy()
            self.entrada.delete(0, "end")




        ctk.CTkButton(ventana, command=entry_process, text="ingresar", anchor="center").pack(pady=10)

        self.cont_players = ctk.CTkLabel(ventana, text="jugadores registrados: 0")
        self.cont_players.pack()




    def ventana_jugadores_4(self):

        ventana = ctk.CTkToplevel()
        ventana.title("Ventana de jugadores")
        ventana.geometry("200x200")
        ventana.resizable(False, False)

        ctk.CTkLabel(ventana, text="Nombre de jugador", anchor="center").pack()
        self.entrada = ctk.CTkEntry(ventana)
        self.entrada.insert(0, "EJ: Pepe360")
        self.entrada.bind("<Button-1>", lambda e: self.entrada.delete(0, 'end'))
        self.entrada.pack()

        jugadores = []  # Declarar la lista fuera de la función entry_process()

        def entry_process():
            jugador = self.entrada.get()
            jugadores.append(jugador)
            cant_players = len(jugadores)
            self.cont_players.configure(text=f"jugadores registrados: {cant_players}")            
            if len(jugadores) == 4:
                with open("jugadores.txt", "a") as file:
                    for nombre in jugadores:
                        file.write(nombre + "\n")
                ventana.destroy()
            self.entrada.delete(0, "end")


        ctk.CTkButton(ventana, command=entry_process, text="ingresar", anchor="center").pack(pady=10)

        self.cont_players = ctk.CTkLabel(ventana, text="jugadores registrados: 0")
        self.cont_players.pack()






    


objeto_func = funciones()


#-------nueva ventana-------
class opciones_pre_juego:

    def __init__(self):
        #---------------------------self-------------------------
        self.root = ctk.CTk()
        self.root.title("Sala de jugadores.")
        self.root.geometry("600x600")

        def salir():
            self.root.destroy()
            win = Inicio()

        botonback = ctk.CTkButton(master=self.root, text = "Volver", command= salir)
        botonback.place(relx=0.8, rely=0.9, anchor=tk.CENTER)

        ctk.CTkButton(self.root, text="2 jugadores", command=objeto_func.ventana_jugadores_2, width=200, height=100).pack(pady=10)
        ctk.CTkButton(self.root, text="3 jugadores", command=objeto_func.ventana_jugadores_3, width=200, height=100).pack(pady=10)
        ctk.CTkButton(self.root, text="4 jugadores", command=objeto_func.ventana_jugadores_4, width=200, height=100).pack(pady=10)




        self.root.mainloop() 
