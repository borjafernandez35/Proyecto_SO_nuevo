﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace WindowsFormsApp1
{
    public partial class Iniciar : Form
    {
        Socket server;
        Boolean Conectado = false;
        Boolean log = false;
        Thread atender;


        delegate void DelegadoRellenador(string mensaje);

        public Iniciar()
        {
            InitializeComponent();
            contraseña.UseSystemPasswordChar = true; //La contraseña no sará visible por defecto
            password.UseSystemPasswordChar = true;
            CheckForIllegalCrossThreadCalls = false; //Necesario para que los elementos de los formularios puedan ser
            //accedidos desde threads diferentes a los que los crearon
        }

        private void AtenderServidor()
        {
            while (true)
            {
                //Recibimos mensaje del servidor
                byte[] msg2 = new byte[500];
                server.Receive(msg2);
                string[] trozos = Encoding.ASCII.GetString(msg2).Split('/');
                int codigo = Convert.ToInt32(trozos[0]);
                string mensaje = trozos[1].Split('\0')[0];
               

                switch (codigo)
                {
                    case 1:  //Registro

                        MessageBox.Show(mensaje);
                        break;
                    case 2:  //Loguearse

                        if (mensaje == "SI")
                        {
                            MessageBox.Show("Ha iniciado sesión correctamente");
                            log = true;
                        }

                        else
                        {
                            MessageBox.Show("Usuario o contraseña incorrecta");
                        }

                        break;

                    case 3:       //Número de jugadores

                        MessageBox.Show(mensaje);
                        break;

                    case 4:     //Puntos de las 3 últimas partidas

                        MessageBox.Show(mensaje);
                        break;

                    case 5:       //Fechas y duración de las partidas ganadas

                        MessageBox.Show(mensaje);
                        break;

                    case 6:     //Nombre de pruebas y puntos que da

                        MessageBox.Show(mensaje);
                        break;

                    case 7:     //Notificación

                        DelegadoRellenador delegado = new DelegadoRellenador(RellenaJugadores);
                        jugador.Invoke(delegado, new object[] { mensaje } ); 

                        break;

                    case 8:

                        string[] invitacion = mensaje.Split('-');
                        DialogResult resultado = MessageBox.Show(invitacion[0] + " quiere jugar contigo", "Aceptas la invitación?", MessageBoxButtons.YesNo);

                        if (resultado == DialogResult.Yes)
                        {
                            string men = "8/" + invitacion[1];
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(men);
                            server.Send(msg);
                        }
                        else
                        {
                            string men = "9/" + invitacion[0];
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(men);
                            server.Send(msg);
                        }

                        break;

                    case 9:

                        MessageBox.Show(mensaje);
                        break;

                    case 10:
                        
                        DelegadoRellenador delegado2 = new DelegadoRellenador(RellenaInvitados);
                        invitados.Invoke(delegado2, new object[] { mensaje } ); 
                       
                        break;

                    case 11:
                        MessageBox.Show(mensaje);
                        break;

                    case 12:

                        DelegadoRellenador delegado3 = new DelegadoRellenador(RellenaChat);
                        chat.Invoke(delegado3, new object[] { mensaje } ); 
                       
                        break;

                }
            }

        }

        public void RellenaJugadores(string mensaje)
        {
            string[] jugadores = mensaje.Split(',');

            jugador.ColumnCount = 1;
            jugador.RowCount = jugadores.Length;
            jugador.ColumnHeadersVisible = false;
            jugador.RowHeadersVisible = false;


            int i = 0;

            foreach (string nombre in jugadores)
            {

                jugador[0, i].Value = nombre;
                i++;
            }
        
        }

        public void RellenaInvitados(string mensaje)
        {
            string[] invitado = mensaje.Split(',');

            invitados.ColumnCount = 1;
            invitados.RowCount = invitado.Length;
            invitados.ColumnHeadersVisible = false;
            invitados.RowHeadersVisible = false;


            int j = 0;

            foreach (string nombre in invitado)
            {

                invitados[0, j].Value = nombre;
                j++;
            }
        }

        public void RellenaChat(string mensaje)
        {
            chat.Items.Add(mensaje);
        }


        private void Mostrar_CheckedChanged(object sender, EventArgs e)
        {
            if (Mostrar.Checked)
            {
                contraseña.UseSystemPasswordChar = false;
            }
            else
            {
                contraseña.UseSystemPasswordChar = true;
            }
        }

        private void conectar_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");
            IPEndPoint ipep = new IPEndPoint(direc, 9070);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                MessageBox.Show("Conectado");
                Conectado = true;
            }

            catch (SocketException)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

            //pongo en marcha el thread que atenderá los mensajes del servidor
            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();
        }

        private void registro_Click(object sender, EventArgs e)
        {
            if (Conectado == true)
            {
                string mensaje = "1/" + nomb.Text + "/" + password.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                nomb.Text = "";
                password.Text = "";
            }

            else
            {
                MessageBox.Show("Hay que conectarse");
            }
        }

        private void inicio_Click(object sender, EventArgs e)
        {

            if (Conectado == true)
            {
                string mensaje = "2/" + nombre.Text + "/" + contraseña.Text;

                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                

                nombre.Text = "";
                contraseña.Text = "";
            }

            else
            {
                MessageBox.Show("Hay que conectarse");
            }
        }


        private void Enviar_Click(object sender, EventArgs e)
        {
            if (Conectado == true && log == true)
            {
                if (partidas.Checked)
                {
                    string mensaje = "5/" + nom.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                }

                else if (historial.Checked)
                {
                    string mensaje = "6/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                }

                else if (puntos.Checked)
                {
                    string mensaje = "4/" + nom.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                }

                else
                {
                    string mensaje = "3/" + id.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                   
                }
            }

            else if (Conectado == false)
            {
                MessageBox.Show("Hay que conectarse");
            }

            else if (log == false)
            {
                MessageBox.Show("Hay que iniciar sesión");
            }
        }

        private void Desconectar_Click(object sender, EventArgs e)
        {
            //Mensaje de desconexión
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            Conectado = false;

            // Nos desconectamos
            atender.Abort();
            server.Shutdown(SocketShutdown.Both);
            server.Close();
            MessageBox.Show("Se ha desconectado");
        }

        private void salir_Click(object sender, EventArgs e)
        {
            if (Conectado == true)
            {
                string mensaje = "0/";

                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
                // Nos desconectamos
                atender.Abort();
                server.Shutdown(SocketShutdown.Both);
                server.Close();
            }

            MessageBox.Show("Gracias y hasta la próxima");
            this.Close();
        }

        private void MostrarRe_CheckedChanged(object sender, EventArgs e)
        {
            if (MostrarRe.Checked)
            {
                password.UseSystemPasswordChar = false;
            }
            else
            {
                password.UseSystemPasswordChar = true;
            }
        }
     

     

        private void conectados_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            string mensaje = "7/" + jugador[0, e.RowIndex].Value;

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
        }

        private void MensajeRecibido(object sender, EventArgs e)
        {
            

        }

        private void send_Click(object sender, EventArgs e)
        {
            string texto = "10/" + mensaje.Text;

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(texto);
            server.Send(msg);
        }

       
    }
}