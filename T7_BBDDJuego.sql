DROP DATABASE IF EXISTS T7_BBDDJuego;
CREATE DATABASE T7_BBDDJuego;

USE T7_BBDDJuego;

CREATE TABLE jugador (
    idJ INT AUTO_INCREMENT, 
    PRIMARY KEY (idJ),    
    nombre VARCHAR(60),
    contraseña VARCHAR(60)
)ENGINE=InnoDB;

INSERT INTO jugador VALUES ('1', 'Juan', 'vfd');
INSERT INTO jugador VALUES ('2', 'Pedro', 'vfd');
INSERT INTO jugador VALUES ('3', 'Alex', 'vfd');
INSERT INTO jugador VALUES ('4', 'Lucia', 'vfd');

CREATE TABLE partida (
    idP INT AUTO_INCREMENT, 
    PRIMARY KEY (idP),
    ganador VARCHAR(20),
    fecha VARCHAR(60),
    duracion VARCHAR(60),
    equipo VARCHAR(100)
)ENGINE=InnoDB;

INSERT INTO partida VALUES ('1', true, '1-2-21', '17.54', 'Los ganadores');

CREATE TABLE historial (
    idJ INT NOT NULL, 
    FOREIGN KEY (idJ) REFERENCES jugador(idJ) ON DELETE CASCADE, 
    idP INT NOT NULL, 
    FOREIGN KEY (idP) REFERENCES partida(idP)
)ENGINE=InnoDB;

INSERT INTO historial VALUES ('1', '1');
INSERT INTO historial VALUES ('2', '1');
INSERT INTO historial VALUES ('3', '1');
INSERT INTO historial VALUES ('4', '1');


