namespace WindowsFormsApp1
{
    partial class Iniciar
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            this.nombre = new System.Windows.Forms.TextBox();
            this.contraseña = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.inicio = new System.Windows.Forms.Button();
            this.Mostrar = new System.Windows.Forms.CheckBox();
            this.registro = new System.Windows.Forms.Button();
            this.historial = new System.Windows.Forms.RadioButton();
            this.nombres = new System.Windows.Forms.RadioButton();
            this.puntos = new System.Windows.Forms.RadioButton();
            this.partidas = new System.Windows.Forms.RadioButton();
            this.Enviar = new System.Windows.Forms.Button();
            this.conectar = new System.Windows.Forms.Button();
            this.Desconectar = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.id = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.nom = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.salir = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.nomb = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.MostrarRe = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.jugador = new System.Windows.Forms.DataGridView();
            this.invitados = new System.Windows.Forms.DataGridView();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.chat = new System.Windows.Forms.ListBox();
            this.mensaje = new System.Windows.Forms.TextBox();
            this.send = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.jugador)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.invitados)).BeginInit();
            this.SuspendLayout();
            // 
            // nombre
            // 
            this.nombre.Location = new System.Drawing.Point(159, 81);
            this.nombre.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.nombre.Name = "nombre";
            this.nombre.Size = new System.Drawing.Size(112, 26);
            this.nombre.TabIndex = 0;
            // 
            // contraseña
            // 
            this.contraseña.Location = new System.Drawing.Point(159, 139);
            this.contraseña.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.contraseña.Name = "contraseña";
            this.contraseña.Size = new System.Drawing.Size(112, 26);
            this.contraseña.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(79, 84);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Nombre";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(52, 142);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 20);
            this.label1.TabIndex = 3;
            this.label1.Text = "Contraseña";
            // 
            // inicio
            // 
            this.inicio.ForeColor = System.Drawing.SystemColors.ControlText;
            this.inicio.Location = new System.Drawing.Point(84, 239);
            this.inicio.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.inicio.Name = "inicio";
            this.inicio.Size = new System.Drawing.Size(172, 51);
            this.inicio.TabIndex = 5;
            this.inicio.Text = "Iniciar";
            this.inicio.UseVisualStyleBackColor = true;
            this.inicio.Click += new System.EventHandler(this.inicio_Click);
            // 
            // Mostrar
            // 
            this.Mostrar.AutoSize = true;
            this.Mostrar.Location = new System.Drawing.Point(83, 190);
            this.Mostrar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Mostrar.Name = "Mostrar";
            this.Mostrar.Size = new System.Drawing.Size(173, 24);
            this.Mostrar.TabIndex = 7;
            this.Mostrar.Text = "Mostrar contraseña";
            this.Mostrar.UseVisualStyleBackColor = true;
            this.Mostrar.CheckedChanged += new System.EventHandler(this.Mostrar_CheckedChanged);
            // 
            // registro
            // 
            this.registro.Location = new System.Drawing.Point(86, 240);
            this.registro.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.registro.Name = "registro";
            this.registro.Size = new System.Drawing.Size(182, 50);
            this.registro.TabIndex = 8;
            this.registro.Text = "Registrarse";
            this.registro.UseVisualStyleBackColor = true;
            this.registro.Click += new System.EventHandler(this.registro_Click);
            // 
            // historial
            // 
            this.historial.AutoSize = true;
            this.historial.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.historial.Location = new System.Drawing.Point(24, 516);
            this.historial.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.historial.Name = "historial";
            this.historial.Size = new System.Drawing.Size(990, 33);
            this.historial.TabIndex = 9;
            this.historial.TabStop = true;
            this.historial.Text = "Dime cuantas pruebas se hicieron en la última partida, su nombre y los puntos que" +
                " dieron";
            this.historial.UseVisualStyleBackColor = true;
            // 
            // nombres
            // 
            this.nombres.AutoSize = true;
            this.nombres.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nombres.Location = new System.Drawing.Point(24, 471);
            this.nombres.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.nombres.Name = "nombres";
            this.nombres.Size = new System.Drawing.Size(653, 33);
            this.nombres.TabIndex = 10;
            this.nombres.TabStop = true;
            this.nombres.Text = "Dime cuantos jugadores hay en una partida y quienes son";
            this.nombres.UseVisualStyleBackColor = true;
            // 
            // puntos
            // 
            this.puntos.AutoSize = true;
            this.puntos.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.puntos.Location = new System.Drawing.Point(24, 592);
            this.puntos.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.puntos.Name = "puntos";
            this.puntos.Size = new System.Drawing.Size(553, 33);
            this.puntos.TabIndex = 11;
            this.puntos.TabStop = true;
            this.puntos.Text = "Dime sus puntos y si ganó sus últimas 3 partidas";
            this.puntos.UseVisualStyleBackColor = true;
            // 
            // partidas
            // 
            this.partidas.AutoSize = true;
            this.partidas.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.partidas.Location = new System.Drawing.Point(24, 635);
            this.partidas.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.partidas.Name = "partidas";
            this.partidas.Size = new System.Drawing.Size(650, 33);
            this.partidas.TabIndex = 12;
            this.partidas.TabStop = true;
            this.partidas.Text = "Dime cuantas partidas ha ganado con su fecha y duración";
            this.partidas.UseVisualStyleBackColor = true;
            // 
            // Enviar
            // 
            this.Enviar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.Enviar.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Enviar.Location = new System.Drawing.Point(1189, 624);
            this.Enviar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Enviar.Name = "Enviar";
            this.Enviar.Size = new System.Drawing.Size(179, 65);
            this.Enviar.TabIndex = 13;
            this.Enviar.Text = "Enviar";
            this.Enviar.UseVisualStyleBackColor = false;
            this.Enviar.Click += new System.EventHandler(this.Enviar_Click);
            // 
            // conectar
            // 
            this.conectar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.conectar.Location = new System.Drawing.Point(860, 32);
            this.conectar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(226, 68);
            this.conectar.TabIndex = 14;
            this.conectar.Text = "Conectar";
            this.conectar.UseVisualStyleBackColor = false;
            this.conectar.Click += new System.EventHandler(this.conectar_Click);
            // 
            // Desconectar
            // 
            this.Desconectar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.Desconectar.Location = new System.Drawing.Point(861, 134);
            this.Desconectar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Desconectar.Name = "Desconectar";
            this.Desconectar.Size = new System.Drawing.Size(225, 68);
            this.Desconectar.TabIndex = 15;
            this.Desconectar.Text = "Desconectar";
            this.Desconectar.UseVisualStyleBackColor = false;
            this.Desconectar.Click += new System.EventHandler(this.Desconectar_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1246, 400);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 20);
            this.label3.TabIndex = 16;
            this.label3.Text = "ID partida";
            // 
            // id
            // 
            this.id.Location = new System.Drawing.Point(1205, 426);
            this.id.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.id.Name = "id";
            this.id.Size = new System.Drawing.Size(148, 26);
            this.id.TabIndex = 17;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(1246, 530);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 20);
            this.label4.TabIndex = 18;
            this.label4.Text = "Nombre";
            // 
            // nom
            // 
            this.nom.Location = new System.Drawing.Point(1205, 556);
            this.nom.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.nom.Name = "nom";
            this.nom.Size = new System.Drawing.Size(148, 26);
            this.nom.TabIndex = 19;
            this.nom.UseWaitCursor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(1059, 354);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(386, 20);
            this.label5.TabIndex = 20;
            this.label5.Text = "Introduzca la ID de la partida para la primera consulta";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(1016, 485);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(481, 20);
            this.label6.TabIndex = 21;
            this.label6.Text = "Introduzca el nombre del jugador para las dos segundas consultas:";
            // 
            // salir
            // 
            this.salir.BackColor = System.Drawing.Color.LightGray;
            this.salir.Location = new System.Drawing.Point(1488, 624);
            this.salir.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.salir.Name = "salir";
            this.salir.Size = new System.Drawing.Size(195, 62);
            this.salir.TabIndex = 22;
            this.salir.Text = "Salir";
            this.salir.UseVisualStyleBackColor = false;
            this.salir.Click += new System.EventHandler(this.salir_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(111, 29);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(109, 20);
            this.label7.TabIndex = 23;
            this.label7.Text = "BIENVENIDO";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.Mostrar);
            this.groupBox1.Controls.Add(this.inicio);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.contraseña);
            this.groupBox1.Controls.Add(this.nombre);
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.groupBox1.Location = new System.Drawing.Point(24, 15);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox1.Size = new System.Drawing.Size(374, 342);
            this.groupBox1.TabIndex = 24;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Inicar";
            // 
            // nomb
            // 
            this.nomb.Location = new System.Drawing.Point(155, 80);
            this.nomb.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.nomb.Name = "nomb";
            this.nomb.Size = new System.Drawing.Size(112, 26);
            this.nomb.TabIndex = 25;
            // 
            // password
            // 
            this.password.Location = new System.Drawing.Point(155, 144);
            this.password.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(112, 26);
            this.password.TabIndex = 26;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(61, 84);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 20);
            this.label8.TabIndex = 27;
            this.label8.Text = "Nombre";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(35, 148);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(92, 20);
            this.label9.TabIndex = 28;
            this.label9.Text = "Contraseña";
            // 
            // MostrarRe
            // 
            this.MostrarRe.AutoSize = true;
            this.MostrarRe.Location = new System.Drawing.Point(86, 190);
            this.MostrarRe.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MostrarRe.Name = "MostrarRe";
            this.MostrarRe.Size = new System.Drawing.Size(173, 24);
            this.MostrarRe.TabIndex = 29;
            this.MostrarRe.Text = "Mostrar contraseña";
            this.MostrarRe.UseVisualStyleBackColor = true;
            this.MostrarRe.CheckedChanged += new System.EventHandler(this.MostrarRe_CheckedChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.MostrarRe);
            this.groupBox2.Controls.Add(this.registro);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.password);
            this.groupBox2.Controls.Add(this.nomb);
            this.groupBox2.Location = new System.Drawing.Point(416, 15);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox2.Size = new System.Drawing.Size(375, 342);
            this.groupBox2.TabIndex = 30;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Registro";
            // 
            // jugador
            // 
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.jugador.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.jugador.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.jugador.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.jugador.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.jugador.DefaultCellStyle = dataGridViewCellStyle2;
            this.jugador.Location = new System.Drawing.Point(1151, 44);
            this.jugador.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.jugador.Name = "jugador";
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.jugador.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.jugador.RowHeadersWidth = 51;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.jugador.RowsDefaultCellStyle = dataGridViewCellStyle4;
            this.jugador.RowTemplate.Height = 24;
            this.jugador.Size = new System.Drawing.Size(270, 234);
            this.jugador.TabIndex = 32;
            this.jugador.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.conectados_CellClick);
            // 
            // invitados
            // 
            this.invitados.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.invitados.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.invitados.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.invitados.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.invitados.Location = new System.Drawing.Point(1448, 44);
            this.invitados.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.invitados.Name = "invitados";
            this.invitados.RowHeadersWidth = 51;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.invitados.RowsDefaultCellStyle = dataGridViewCellStyle5;
            this.invitados.RowTemplate.Height = 24;
            this.invitados.Size = new System.Drawing.Size(300, 234);
            this.invitados.TabIndex = 33;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(1544, 15);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(116, 20);
            this.label10.TabIndex = 34;
            this.label10.Text = "Sala de espera";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(1250, 15);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(95, 20);
            this.label11.TabIndex = 35;
            this.label11.Text = "Conectados";
            // 
            // chat
            // 
            this.chat.FormattingEnabled = true;
            this.chat.ItemHeight = 20;
            this.chat.Location = new System.Drawing.Point(1815, 44);
            this.chat.Name = "chat";
            this.chat.Size = new System.Drawing.Size(257, 424);
            this.chat.TabIndex = 36;
            // 
            // mensaje
            // 
            this.mensaje.Location = new System.Drawing.Point(1815, 485);
            this.mensaje.Name = "mensaje";
            this.mensaje.Size = new System.Drawing.Size(178, 26);
            this.mensaje.TabIndex = 37;
            // 
            // send
            // 
            this.send.Location = new System.Drawing.Point(1999, 478);
            this.send.Name = "send";
            this.send.Size = new System.Drawing.Size(75, 35);
            this.send.TabIndex = 38;
            this.send.Text = "SEND";
            this.send.UseVisualStyleBackColor = true;
            this.send.Click += new System.EventHandler(this.send_Click);
            // 
            // Iniciar
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::WindowsFormsApp1.Properties.Resources.inline_image_preview;
            this.ClientSize = new System.Drawing.Size(2130, 751);
            this.Controls.Add(this.send);
            this.Controls.Add(this.mensaje);
            this.Controls.Add(this.chat);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.invitados);
            this.Controls.Add(this.jugador);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.salir);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.nom);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.id);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.Desconectar);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.Enviar);
            this.Controls.Add(this.partidas);
            this.Controls.Add(this.puntos);
            this.Controls.Add(this.nombres);
            this.Controls.Add(this.historial);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Iniciar";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.jugador)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.invitados)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox nombre;
        private System.Windows.Forms.TextBox contraseña;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button inicio;
        private System.Windows.Forms.CheckBox Mostrar;
        private System.Windows.Forms.Button registro;
        private System.Windows.Forms.RadioButton historial;
        private System.Windows.Forms.RadioButton nombres;
        private System.Windows.Forms.RadioButton puntos;
        private System.Windows.Forms.RadioButton partidas;
        private System.Windows.Forms.Button Enviar;
        private System.Windows.Forms.Button conectar;
        private System.Windows.Forms.Button Desconectar;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox id;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox nom;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button salir;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox nomb;
        private System.Windows.Forms.TextBox password;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox MostrarRe;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView jugador;
        private System.Windows.Forms.DataGridView invitados;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ListBox chat;
        private System.Windows.Forms.TextBox mensaje;
        private System.Windows.Forms.Button send;
    }
}

