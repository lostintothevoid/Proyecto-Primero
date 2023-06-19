import tkinter

#---------------------------Ventana-------------------------
ventana = tkinter.Tk()
ventana.title("UNON'T_Alpha_test")
ventana.geometry("600x600")
ventana.resizable(0,0)
#------------------------Controles de ventana---------------

def inicio():
    tkinter.Label(ventana, text="Iniciar partida").pack()

def salir():
    ventana.destroy()


ventana.mainloop()