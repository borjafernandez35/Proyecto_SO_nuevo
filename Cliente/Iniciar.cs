using System;
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
                byte[] msg2 = new byte[300];
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

                        string[] jugadores = mensaje.Split(',');

                        conectados.ColumnCount = 1;
                        conectados.RowCount = jugadores.Length;
                        conectados.ColumnHeadersVisible = false;
                        conectados.RowHeadersVisible = false;

                   
                        int i = 0;

                        foreach (string nombre in jugadores)
                        {
                            conectados[0, i].Value = nombre;
                            i++;
                        }

                        break;
                }
            }

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
            IPAddress direc = IPAddress.Parse("147.83.117.22");
            IPEndPoint ipep = new IPEndPoint(direc, 50070);


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
    }
}