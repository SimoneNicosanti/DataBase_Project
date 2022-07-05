-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema my_english_school
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `my_english_school` ;

-- -----------------------------------------------------
-- Schema my_english_school
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `my_english_school` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `my_english_school` ;

-- -----------------------------------------------------
-- Table `my_english_school`.`Livello`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Livello` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Livello` (
  `nomeLivello` VARCHAR(45) NOT NULL,
  `libro` VARCHAR(45) NOT NULL,
  `esame` SMALLINT NOT NULL,
  PRIMARY KEY (`nomeLivello`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Corso`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Corso` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Corso` (
  `codiceCorso` INT NOT NULL AUTO_INCREMENT,
  `nomeLivello` VARCHAR(45) NOT NULL,
  `dataAttivazione` DATE NOT NULL,
  `numeroAllievi` INT NOT NULL DEFAULT '0',
  PRIMARY KEY (`codiceCorso`),
  INDEX `fk_Corso_1_idx` (`nomeLivello` ASC) VISIBLE,
  CONSTRAINT `fk_Corso_1`
    FOREIGN KEY (`nomeLivello`)
    REFERENCES `my_english_school`.`Livello` (`nomeLivello`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Allievo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Allievo` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Allievo` (
  `nomeAllievo` VARCHAR(100) NOT NULL,
  `telefonoAllievo` VARCHAR(15) NOT NULL,
  `numeroAssenze` INT NOT NULL DEFAULT 0,
  `dataIscrizione` DATE NOT NULL,
  `codiceCorso` INT NOT NULL,
  PRIMARY KEY (`nomeAllievo`),
  INDEX `fk_Allievo_1_idx` (`codiceCorso` ASC) VISIBLE,
  CONSTRAINT `fk_Allievo_1`
    FOREIGN KEY (`codiceCorso`)
    REFERENCES `my_english_school`.`Corso` (`codiceCorso`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Assenza`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Assenza` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Assenza` (
  `dataAssenza` DATE NOT NULL,
  `nomeAllievo` VARCHAR(100) NOT NULL,
  `orarioAssenza` TIME NOT NULL,
  INDEX `fk_Assenza_1_idx` (`nomeAllievo` ASC) VISIBLE,
  PRIMARY KEY (`nomeAllievo`, `orarioAssenza`, `dataAssenza`),
  CONSTRAINT `fk_Assenza_1`
    FOREIGN KEY (`nomeAllievo`)
    REFERENCES `my_english_school`.`Allievo` (`nomeAllievo`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`AttivitaCulturale`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`AttivitaCulturale` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`AttivitaCulturale` (
  `codiceAttivita` INT NOT NULL AUTO_INCREMENT,
  `dataAttivita` DATE NOT NULL,
  `orarioAttivita` TIME NOT NULL,
  `tipoAttivita` SMALLINT NOT NULL COMMENT 'tipoAttività. 	- 0 <---> proiezione\n				- 1 <---> conferenza',
  `titoloFilm` VARCHAR(100) NULL,
  `registaFilm` VARCHAR(100) NULL,
  `conferenziere` VARCHAR(100) NULL,
  `argomentoConferenza` VARCHAR(100) NULL,
  PRIMARY KEY (`codiceAttivita`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Utenti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Utenti` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Utenti` (
  `username` VARCHAR(100) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `ruolo` ENUM('amministrazione', 'segreteria', 'insegnante') NOT NULL,
  PRIMARY KEY (`username`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Insegnante`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Insegnante` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Insegnante` (
  `nomeInsegnante` VARCHAR(100) NOT NULL,
  `nazioneInsegnante` VARCHAR(45) NOT NULL,
  `indirizzoInsegnante` VARCHAR(100) NOT NULL,
  `username` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`nomeInsegnante`),
  INDEX `fk_Insegnante_1_idx` (`username` ASC) VISIBLE,
  UNIQUE INDEX `username_UNIQUE` (`username` ASC) VISIBLE,
  CONSTRAINT `fk_Insegnante_1`
    FOREIGN KEY (`username`)
    REFERENCES `my_english_school`.`Utenti` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Docenza`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Docenza` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Docenza` (
  `codiceCorso` INT NOT NULL,
  `nomeInsegnante` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`codiceCorso`, `nomeInsegnante`),
  INDEX `fk_Docenza_1_idx` (`nomeInsegnante` ASC) VISIBLE,
  INDEX `fk_Docenza_2_idx` (`codiceCorso` ASC) VISIBLE,
  CONSTRAINT `fk_Docenza_1`
    FOREIGN KEY (`nomeInsegnante`)
    REFERENCES `my_english_school`.`Insegnante` (`nomeInsegnante`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT,
  CONSTRAINT `fk_Docenza_2`
    FOREIGN KEY (`codiceCorso`)
    REFERENCES `my_english_school`.`Corso` (`codiceCorso`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`LezioneCorso`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`LezioneCorso` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`LezioneCorso` (
  `giornoSettimana` ENUM('Lun', 'Mar', 'Mer', 'Gio', 'Ven', 'Sab', 'Dom') NOT NULL,
  `orarioInizio` TIME NOT NULL,
  `codiceCorso` INT NOT NULL,
  `durata` INT NOT NULL,
  `insegnanteLezione` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`giornoSettimana`, `orarioInizio`, `codiceCorso`),
  INDEX `fk_LezioneCorso_1_idx` (`codiceCorso` ASC) VISIBLE,
  INDEX `fk_LezioneCorso_2_idx` (`insegnanteLezione` ASC) VISIBLE,
  CONSTRAINT `fk_LezioneCorso_1`
    FOREIGN KEY (`codiceCorso`)
    REFERENCES `my_english_school`.`Corso` (`codiceCorso`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT,
  CONSTRAINT `fk_LezioneCorso_2`
    FOREIGN KEY (`insegnanteLezione`)
    REFERENCES `my_english_school`.`Insegnante` (`nomeInsegnante`)
    ON DELETE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`LezionePrivata`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`LezionePrivata` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`LezionePrivata` (
  `dataLezione` DATE NOT NULL,
  `orarioLezione` TIME NOT NULL,
  `nomeInsegnante` VARCHAR(100) NOT NULL,
  `durataLezione` INT NOT NULL,
  `nomeAllievo` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`dataLezione`, `orarioLezione`, `nomeInsegnante`),
  INDEX `fk_LezionePrivata_1_idx` (`nomeInsegnante` ASC) VISIBLE,
  INDEX `fk_LezionePrivata_2_idx` (`nomeAllievo` ASC) VISIBLE,
  CONSTRAINT `fk_LezionePrivata_1`
    FOREIGN KEY (`nomeInsegnante`)
    REFERENCES `my_english_school`.`Insegnante` (`nomeInsegnante`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT,
  CONSTRAINT `fk_LezionePrivata_2`
    FOREIGN KEY (`nomeAllievo`)
    REFERENCES `my_english_school`.`Allievo` (`nomeAllievo`)
    ON DELETE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `my_english_school`.`Partecipazione`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `my_english_school`.`Partecipazione` ;

CREATE TABLE IF NOT EXISTS `my_english_school`.`Partecipazione` (
  `codiceAttivita` INT NOT NULL,
  `nomeAllievo` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`codiceAttivita`, `nomeAllievo`),
  INDEX `fk_Partecipazione_2_idx` (`nomeAllievo` ASC) VISIBLE,
  INDEX `fk_Partecipazione_1_idx` (`codiceAttivita` ASC) VISIBLE,
  CONSTRAINT `fk_Partecipazione_1`
    FOREIGN KEY (`codiceAttivita`)
    REFERENCES `my_english_school`.`AttivitaCulturale` (`codiceAttivita`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT,
  CONSTRAINT `fk_Partecipazione_2`
    FOREIGN KEY (`nomeAllievo`)
    REFERENCES `my_english_school`.`Allievo` (`nomeAllievo`)
    ON DELETE RESTRICT)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;

USE `my_english_school` ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`login`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `login`(
	IN var_username VARCHAR(100), 
	IN var_password VARCHAR(45), 
    OUT var_role INT) 
BEGIN

	DECLARE var_enum_role ENUM("amministrazione","segreteria","insegnante") ;
    
	SELECT `ruolo` 
    FROM `Utenti`
    WHERE `username` = var_username AND `password` = SHA1(var_password)
    INTO var_enum_role ;
    
    IF var_enum_role = "amministrazione" THEN
		SET var_role = 0 ;
	ELSEIF var_enum_role = "segreteria" THEN
		SET var_role = 1 ;
	ELSEIF var_enum_role = "insegnante" THEN
		SET var_role = 2 ;
	ELSE
		SET var_role = 3 ;
	END IF ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure riavvia_anno
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`riavvia_anno`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `riavvia_anno` ()
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE ;
	START TRANSACTION ;
		DELETE FROM `Partecipazione` ;
        DELETE FROM `AttivitaCulturale` ;
        DELETE FROM `Assenza` ;
        DELETE FROM `LezioneCorso` ;
        DELETE FROM `Docenza` ;
        DELETE FROM `LezionePrivata` ;
        
		DELETE FROM `Allievo` ;
        DELETE FROM `Insegnante` ;
        
		DELETE FROM `Corso` ;
		DELETE FROM `Livello` ;
        
        DELETE FROM `Utenti` 
			WHERE `username` <> 'amministrazione' AND  `username` <> 'segreteria' ;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_livello
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_livello`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_livello` (
	IN var_nome_livello VARCHAR(45), 
    IN var_nome_libro VARCHAR(45), 
    IN var_has_exam BOOLEAN)
BEGIN
	INSERT INTO `Livello`(`nomeLivello`, `libro`, `esame`) 
		VALUES(var_nome_livello, var_nome_libro, var_has_exam) ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_corso
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_corso`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_corso` (
	IN var_livello_corso VARCHAR(45), 
    IN var_data_attivazione DATE, 
    OUT var_codice_corso INT)
BEGIN
    
    declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
	START TRANSACTION ;
		INSERT INTO `Corso`(`nomeLivello`, `dataAttivazione`, `codiceCorso`, `numeroAllievi`) 
			VALUES(var_livello_corso, var_data_attivazione, NULL, DEFAULT) ;
        
		SELECT LAST_INSERT_ID() INTO var_codice_corso ;
	
    COMMIT ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_allievo
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_allievo`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_allievo` (
	IN var_nome_allievo VARCHAR(100), 
    IN var_telefono_allievo VARCHAR(15), 
    IN var_data_iscrizione DATE, 
    IN var_codice_corso INT)
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
	
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		INSERT INTO `Allievo`(nomeAllievo, telefonoAllievo, dataIscrizione, codiceCorso)
			VALUES(var_nome_allievo, var_telefono_allievo, var_data_iscrizione, var_codice_corso) ;
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_insegnante
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_insegnante`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_insegnante` (
	IN var_nome_insegnante VARCHAR(100), 
	IN var_nazione_insegnante VARCHAR(100), 
    IN var_indirizzo_insegnante VARCHAR(100),
    IN var_username_insegnante VARCHAR(100))
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
    
		INSERT INTO Utenti
			VALUES(var_username_insegnante, SHA1('insegnante'), 'insegnante') ;
	
		INSERT INTO `Insegnante` 
			VALUES (var_nome_insegnante, var_nazione_insegnante, var_indirizzo_insegnante, var_username_insegnante) ;
	
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_lezione
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_lezione`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_lezione` (
	IN var_giorno_settimana ENUM('Lun', 'Mar', 'Mer', 'Gio', 'Ven', 'Sab', 'Dom'), 
    IN var_orario_inizio TIME, 
    IN var_codice_corso INT, 
    IN var_durata INT, 
    IN var_insegnante_lezione VARCHAR(100))
    
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
	START TRANSACTION ;
		
        IF (verificaOrarioDurataValidi(var_orario_inizio, var_durata) != 1) THEN
			SIGNAL SQLSTATE '45009' SET MESSAGE_TEXT = 'Orario/Durata Inseriti Non Validi' ;
		END IF ;
			
		INSERT INTO `LezioneCorso`
			VALUES (var_giorno_settimana, var_orario_inizio, var_codice_corso, var_durata, var_insegnante_lezione) ;
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure assegna_corso
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`assegna_corso`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `assegna_corso` (
	IN var_codice_corso INT, 
    IN var_nome_insegnante VARCHAR(100))
BEGIN
	INSERT INTO `Docenza`
		VALUES(var_codice_corso, var_nome_insegnante) ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure prenota_lezione_privata
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`prenota_lezione_privata`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `prenota_lezione_privata` (
	IN var_data DATE, 
    IN var_orario TIME, 
    IN var_insegnante VARCHAR(100),
    IN var_durata INT,
    IN var_allievo VARCHAR(100))
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE ;
    START TRANSACTION ;
    
		IF (verificaOrarioDurataValidi(var_orario, var_durata) != 1) THEN
			SIGNAL SQLSTATE '45049' SET MESSAGE_TEXT = 'Orario/Durata Inseriti Non Validi' ;
        END IF ;
        
		INSERT INTO LezionePrivata 
			VALUES (var_data, var_orario, var_insegnante, var_durata, var_allievo) ;
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure organizza_attivita_culturale
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`organizza_attivita_culturale`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `organizza_attivita_culturale` (
	IN var_data_attivita DATE, 
    IN var_orario_attivita TIME, 
    IN var_tipo_attivita SMALLINT, 
    IN var_titolo_film VARCHAR(100), 
    IN var_regista_film VARCHAR(100), 
    IN var_conferenziere VARCHAR(100), 
    IN var_argomento_conferenza VARCHAR(100),
    OUT var_codice_attivita INT)
    
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
	
		IF (HOUR(var_orario_attivita) >= 24) THEN
			SIGNAL SQLSTATE '45004' SET MESSAGE_TEXT = 'Orario Non Valido: Orario Inizio Maggiore di 24' ;
		END IF ;
        
        # 0 = proiezione ; 1 = conferenza
        IF (var_tipo_attivita != 0 AND var_tipo_attivita != 1) THEN
			SIGNAL SQLSTATE '45004' SET MESSAGE_TEXT = 'Tipo Attività Specificato Non Valido' ;
        END IF ;
        
        
        IF var_tipo_attivita = 0 AND (var_conferenziere IS NOT NULL OR var_argomento_conferenza IS NOT NULL OR var_titolo_film IS NULL OR var_regista_film IS NULL) THEN
			SIGNAL SQLSTATE '45004' SET MESSAGE_TEXT = 'Informazioni Non Valide Per Proiezione' ;
		ELSEIF var_tipo_attivita = 1 AND (var_conferenziere IS NULL OR var_argomento_conferenza IS NULL OR var_titolo_film IS NOT NULL OR var_regista_film IS NOT NULL) THEN
				SIGNAL SQLSTATE '45004' SET MESSAGE_TEXT = 'Informazioni Non Valide Per Conferenza' ;
		END IF ;
        
        
		INSERT INTO `AttivitaCulturale`
			VALUES (NULL, var_data_attivita, var_orario_attivita, var_tipo_attivita, var_titolo_film, var_regista_film, var_conferenziere, var_argomento_conferenza) ;
            
		SELECT LAST_INSERT_ID() INTO var_codice_attivita ;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_partecipazione
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_partecipazione`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_partecipazione` (
	IN var_codice_attivita INT, 
    IN var_nome_allievo VARCHAR(100))
    
BEGIN
	INSERT INTO `Partecipazione`
		VALUES (var_codice_attivita, var_nome_allievo) ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_corsi
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_corsi`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_corsi` ()
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		SELECT * 
        FROM `Corso` 
        ORDER BY nomeLivello, codiceCorso;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_attivita
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_attivita`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_attivita` ()
BEGIN

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		SELECT * 
		FROM AttivitaCulturale
		WHERE dataAttivita > NOW() 
		ORDER BY dataAttivita, orarioAttivita ;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_assenza
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`aggiungi_assenza`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `aggiungi_assenza` (
	IN var_nome_allievo VARCHAR(100), 
    IN var_data_assenza DATE, 
    IN var_orario_assenza TIME)
    
BEGIN
    
    declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ ;
	START TRANSACTION ;
        
        INSERT INTO Assenza
			VALUES(var_data_assenza, var_nome_allievo, var_orario_assenza) ;

    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- function conversioneDataGiorno
-- -----------------------------------------------------

USE `my_english_school`;
DROP function IF EXISTS `my_english_school`.`conversioneDataGiorno`;

DELIMITER $$
USE `my_english_school`$$
CREATE FUNCTION conversioneDataGiorno (
	var_data DATE) 
    RETURNS ENUM('Lun', 'Mar', 'Mer', 'Gio', 'Ven', 'Sab', 'Dom')
    DETERMINISTIC
    CONTAINS SQL
    
BEGIN
	DECLARE var_day_name ENUM('Lun', 'Mar', 'Mer', 'Gio', 'Ven', 'Sab', 'Dom') ;
    DECLARE var_day_num INT DEFAULT DAYOFWEEK(var_data) ;
        
	IF var_day_num = 1 THEN SET var_day_name = 'Dom' ;
	ELSEIF var_day_num = 2 THEN SET var_day_name = 'Lun' ;
	ELSEIF var_day_num = 3 THEN SET var_day_name = 'Mar' ;
	ELSEIF var_day_num = 4 THEN SET var_day_name = 'Mer' ;
	ELSEIF var_day_num = 5 THEN SET var_day_name = 'Gio' ;
	ELSEIF var_day_num = 6 THEN SET var_day_name = 'Ven' ;
	ELSE SET var_day_name = 'Sab' ;
	END IF ;
    
    RETURN var_day_name ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_docenze
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_docenze`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_docenze` ()
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		SELECT D.codiceCorso, C.nomeLivello, D.nomeInsegnante
        FROM Docenza AS D JOIN Corso AS C ON D.codiceCorso = C.codiceCorso
        ORDER BY C.nomeLivello, D.codiceCorso ;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_agenda
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`genera_agenda`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `genera_agenda` (
	IN var_username_insegnante VARCHAR(100), 
    IN var_week_index INT)
BEGIN

	DECLARE var_insegnante VARCHAR(100) ;
    ## Prendo la settimana coinvolta nella richiesta
    DECLARE var_week DATE DEFAULT DATE_ADD(NOW(), INTERVAL var_week_index WEEK) ; ## Prendo una data della settimana richiesta
    DECLARE var_first_date DATE DEFAULT DATE_SUB(var_week, INTERVAL WEEKDAY(var_week) DAY) ; ## Prendo prima data di settimana 
    DECLARE var_last_date DATE DEFAULT DATE_ADD(var_first_date, INTERVAL 6 DAY) ; ## Prendo ultima data settimana
    DECLARE var_week_date DATE DEFAULT var_first_date ;
    
    ## Creo Tabella Temporanea in cui inserire le informazioni di interesse
    DROP TABLE IF EXISTS ImpegnoInsegnante ;
    CREATE TEMPORARY TABLE ImpegnoInsegnante (
		dataImpegno DATE ,
        orarioInizio TIME ,
        orarioFine TIME ,
        tipoImpegno ENUM('C','P') , ## C = Corso ; P = Privata
        corso INT ,
        livello VARCHAR(45) ,
        allievo VARCHAR(100)) ;
    
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		
		SELECT nomeInsegnante
		FROM Insegnante
		WHERE username = var_username_insegnante 
		INTO var_insegnante ;

		# Il ciclo viene fatto sulle date che ricadono in quella settimana
		loop_data: LOOP
				IF (var_week_date > var_last_date) THEN
					LEAVE loop_data ;
				END IF ;
				
                INSERT INTO ImpegnoInsegnante 
					SELECT var_week_date, L.orarioInizio, L.orarioInizio + INTERVAL L.durata MINUTE, 'C', C.codiceCorso, C.nomeLivello, NULL
                    FROM LezioneCorso AS L JOIN Corso AS C ON L.codiceCorso = C.codiceCorso
					WHERE L.insegnanteLezione = var_insegnante AND conversioneDataGiorno(var_week_date) = L.giornoSettimana ;
				
				SET var_week_date = DATE_ADD(var_week_date, INTERVAL 1 DAY) ;
		END LOOP ;
    
        INSERT INTO ImpegnoInsegnante
			SELECT L.dataLezione, L.orarioLezione, L.orarioLezione + INTERVAL L.durataLezione MINUTE, 'P', NULL, NULL, L.nomeAllievo
            FROM LezionePrivata AS L
            WHERE L.nomeInsegnante = var_insegnante AND L.dataLezione BETWEEN var_first_date AND var_last_date ;
            
    
		SET var_week_date = var_first_date ;
		select_loop : LOOP
			IF (var_week_date > var_last_date) THEN
				LEAVE select_loop ;
			END IF ;
        
			
            # Ritornati 7 result set, uno per ogni giorno
			SELECT *
			FROM ImpegnoInsegnante
            WHERE dataImpegno = var_week_date
			ORDER BY dataImpegno, orarioInizio ;
            
            SET var_week_date = DATE_ADD(var_week_date, INTERVAL 1 DAY) ; 
		END LOOP ;
        
    COMMIT ;
    
    DROP TEMPORARY TABLE ImpegnoInsegnante ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- function verifica_orari_compatibili
-- -----------------------------------------------------

USE `my_english_school`;
DROP function IF EXISTS `my_english_school`.`verifica_orari_compatibili`;

DELIMITER $$
USE `my_english_school`$$
CREATE FUNCTION `verifica_orari_compatibili` (
	var_inizio_1 TIME, 
    var_fine_1 TIME, 
    var_inizio_2 TIME, 
    var_fine_2 TIME) 
    RETURNS INT
    DETERMINISTIC
    
BEGIN
	## Torno TRUE se gli orari sono compatibili, false altrimenti
	IF (var_fine_1 <= var_inizio_2 OR var_fine_2 <= var_inizio_1) THEN
		RETURN TRUE ;
	ELSE RETURN FALSE ;
    END IF ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure report_assenze_corso
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`report_assenze_corso`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `report_assenze_corso` (IN var_codice_corso INT)
BEGIN

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		SELECT nomeAllievo, numeroAssenze
		FROM Allievo
		WHERE codiceCorso = var_codice_corso ;
	COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_report_insegnante
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`genera_report_insegnante`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `genera_report_insegnante` (
	IN var_insegnante VARCHAR(100), 
    IN var_month_index INT,
    IN var_year YEAR) 

    
BEGIN
	
	# Prendo giorno del mese
	DECLARE var_date DATE DEFAULT MAKEDATE(var_year, 1 + 32*var_month_index); # Prendo una data qualunque in quel mese e anno
    DECLARE var_month_last_date DATE DEFAULT LAST_DAY(var_date); # Prendo ultima data del mese in anno
    DECLARE var_month_first_date DATE DEFAULT DATE_SUB(var_month_last_date, INTERVAL (DAYOFMONTH(var_month_last_date) - 1) DAY) ; # Prendo la prima data del mese in anno
    
    DECLARE var_month_date DATE DEFAULT var_month_first_date ; ## Variabile per ciclo su date del mese
    
    declare exit handler for sqlexception ## Dichiarazione Gestore eccezione sollevata dal Trigger
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
    DROP TABLE IF EXISTS ReportInsegnante ;
    CREATE TEMPORARY TABLE ReportInsegnante(
		dataLezione DATE,
        orarioInizio TIME,
        durata INT,
        tipoLezione ENUM('C','P')) ;
        
	
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
    
		IF (var_month_index < 0 || var_month_index > 11) THEN
			SIGNAL SQLSTATE '45059' SET MESSAGE_TEXT = 'Indice Mese Non Valido' ;
		END IF ;
		
        
		month_date_loop: LOOP
			IF (var_month_date > var_month_last_date) THEN
				LEAVE month_date_loop ;
			END IF ;
            
            INSERT INTO ReportInsegnante
				SELECT var_month_date, L.orarioInizio, L.durata, 'C'
                FROM LezioneCorso AS L
                WHERE L.insegnanteLezione = var_insegnante AND conversioneDataGiorno(var_month_date) = L.giornoSettimana ;
            
            SET var_month_date = DATE_ADD(var_month_date, INTERVAL 1 DAY) ; ## Incremento variabile del loop
        END LOOP ;
        
        
        INSERT INTO ReportInsegnante
			SELECT L.dataLezione, L.orarioLezione, L.durataLezione, 'P'
            FROM LezionePrivata AS L
            WHERE L.nomeInsegnante = var_insegnante AND L.dataLezione BETWEEN var_month_first_date AND var_month_last_date ;
    
		SELECT *
		FROM ReportInsegnante
		ORDER BY dataLezione, orarioInizio ;
    
    COMMIT ;
    DROP TEMPORARY TABLE ReportInsegnante ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_insegnanti_liberi
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_insegnanti_liberi`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_insegnanti_liberi` (
	IN var_data DATE, 
    IN var_orario TIME, 
    IN var_durata INT)
BEGIN

	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
    
		IF (verificaOrarioDurataValidi(var_orario, var_durata) != 1) THEN
			SIGNAL SQLSTATE '45009' SET MESSAGE_TEXT = 'Orario/Durata Inseriti Non Validi' ;
        END IF ;
    
		SELECT I.nomeInsegnante
		FROM Insegnante AS I
		WHERE 
			I.nomeInsegnante NOT IN (
				SELECT insegnanteLezione
				FROM LezioneCorso
				WHERE
					giornoSettimana = conversioneDataGiorno(var_data) AND
					NOT verifica_orari_compatibili(var_orario, var_orario + INTERVAL var_durata MINUTE, orarioInizio, orarioInizio + INTERVAL durata MINUTE)
				) 
			AND
			I.nomeInsegnante NOT IN (
				SELECT nomeInsegnante
				FROM LezionePrivata
				WHERE 
					var_data = dataLezione AND
					NOT verifica_orari_compatibili(var_orario, var_orario + INTERVAL var_durata MINUTE, orarioLezione, orarioLezione + INTERVAL durataLezione MINUTE)
				) ;
        
	COMMIT ;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_livelli
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_livelli`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_livelli` ()
BEGIN
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
    
        SELECT *
        FROM Livello
        ORDER BY nomeLivello ;
        
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_insegnanti
-- -----------------------------------------------------

USE `my_english_school`;
DROP procedure IF EXISTS `my_english_school`.`recupera_insegnanti`;

DELIMITER $$
USE `my_english_school`$$
CREATE PROCEDURE `recupera_insegnanti` ()
BEGIN
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
    START TRANSACTION ;
		SELECT nomeInsegnante, nazioneInsegnante, indirizzoInsegnante
        FROM Insegnante 
        ORDER BY nomeInsegnante ;
    COMMIT ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- function verificaOrarioDurataValidi
-- -----------------------------------------------------

USE `my_english_school`;
DROP function IF EXISTS `my_english_school`.`verificaOrarioDurataValidi`;

DELIMITER $$
USE `my_english_school`$$
CREATE FUNCTION `verificaOrarioDurataValidi` (
	var_orario TIME, 
    var_durata INT) 
    RETURNS INT
    DETERMINISTIC
    
BEGIN
	# Controllo validità di orario e durata
	IF (HOUR(var_orario) >= 24) THEN
		RETURN 0 ;
	ELSEIF (var_durata <= 0) THEN
		RETURN 0 ;
	ELSEIF (HOUR(var_orario + INTERVAL var_durata MINUTE) >= 24) THEN
		RETURN 0 ;
	END IF ;
    
    RETURN 1 ;
END$$

DELIMITER ;
SET SQL_MODE = '';
DROP USER IF EXISTS login;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'login' IDENTIFIED BY 'Login@1234';

GRANT EXECUTE ON procedure `my_english_school`.`login` TO 'login';
SET SQL_MODE = '';
DROP USER IF EXISTS amministrazione;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'amministrazione' IDENTIFIED BY 'Amministrazione@1234';

GRANT EXECUTE ON procedure `my_english_school`.`riavvia_anno` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_livello` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_corso` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_insegnante` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`assegna_corso` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`organizza_attivita_culturale` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_corsi` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_lezione` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_docenze` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`genera_report_insegnante` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_insegnanti` TO 'amministrazione';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_livelli` TO 'amministrazione';
SET SQL_MODE = '';
DROP USER IF EXISTS segreteria;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'segreteria' IDENTIFIED BY 'Segreteria@1234';

GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_allievo` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_partecipazione` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_corsi` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_attivita` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`aggiungi_assenza` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`prenota_lezione_privata` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`report_assenze_corso` TO 'segreteria';
GRANT EXECUTE ON procedure `my_english_school`.`recupera_insegnanti_liberi` TO 'segreteria';
SET SQL_MODE = '';
DROP USER IF EXISTS insegnante;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'insegnante' IDENTIFIED BY 'Insegnante@1234';

GRANT EXECUTE ON procedure `my_english_school`.`genera_agenda` TO 'insegnante';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `my_english_school`.`Utenti`
-- -----------------------------------------------------
START TRANSACTION;
USE `my_english_school`;
INSERT INTO `my_english_school`.`Utenti` (`username`, `password`, `ruolo`) VALUES ('amministrazione', '156b7dfafeeef4435ece5367c0e5a5cfd5ae1390', 'amministrazione');
INSERT INTO `my_english_school`.`Utenti` (`username`, `password`, `ruolo`) VALUES ('segreteria', '02cad8ee4fb1cc60f6a485316007c9d709293cbd', 'segreteria');

COMMIT;

USE `my_english_school`;

DELIMITER $$

USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`Allievo_AFTER_INSERT` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`Allievo_AFTER_INSERT` AFTER INSERT ON `Allievo` FOR EACH ROW

BEGIN
    UPDATE `Corso`
    SET Corso.numeroAllievi = Corso.numeroAllievi + 1 
    WHERE Corso.codiceCorso = new.codiceCorso ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`Assenza_BEFORE_INSERT` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`Assenza_BEFORE_INSERT` BEFORE INSERT ON `Assenza` FOR EACH ROW
BEGIN
	
	DECLARE var_esiste_lezione INT DEFAULT 0 ;
    DECLARE var_codice_corso INT ;
    
    SELECT codiceCorso
    FROM Allievo
    WHERE nomeAllievo = new.nomeAllievo 
    INTO var_codice_corso ;
    
    SELECT count(*)
    FROM LezioneCorso
    WHERE 
		codiceCorso = var_codice_corso AND
		giornoSettimana = conversioneDataGiorno(new.dataAssenza) AND
        orarioInizio = new.orarioAssenza
	INTO var_esiste_lezione ;
    
    IF (var_esiste_lezione = 0) THEN
		SIGNAL SQLSTATE '45001' SET MESSAGE_TEXT = "Non esistono Lezioni del Corso di Allievo che combacino" ;
    END IF ;
    
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`Assenza_AFTER_INSERT` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`Assenza_AFTER_INSERT` AFTER INSERT ON `Assenza` FOR EACH ROW
BEGIN
	UPDATE Allievo
    SET numeroAssenze = numeroAssenze + 1
    WHERE nomeAllievo = new.nomeAllievo;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezioneCorso_BEFORE_INSERT` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezioneCorso_BEFORE_INSERT` BEFORE INSERT ON `LezioneCorso` FOR EACH ROW
BEGIN
	#CONTROLLO NON CONFLITTO DI ORARI CON ALTRE LEZIONI DI CORSI
    
    DECLARE var_has_conflict INT DEFAULT 0;
    
    SELECT count(*)
    FROM LezioneCorso
    WHERE 
		insegnantelezione = new.insegnanteLezione AND 
        giornoSettimana = new.giornoSettimana AND
        NOT verifica_orari_compatibili(new.orarioInizio, new.orarioInizio + INTERVAL new.durata MINUTE, orarioInizio, orarioInizio + INTERVAL durata MINUTE)
	INTO var_has_conflict ;
    
    IF var_has_conflict > 0 THEN 
		SIGNAL SQLSTATE '45005' SET MESSAGE_TEXT = 'Insegnante ha una lezione di un altro corso' ;
    END IF ;
    
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezioneCorso_BEFORE_INSERT_1` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezioneCorso_BEFORE_INSERT_1` BEFORE INSERT ON `LezioneCorso` FOR EACH ROW
BEGIN

	## Controllo Docenza Assegnata
	DECLARE var_docenze INT DEFAULT 0;
    
    SELECT count(*)
    FROM Docenza
    WHERE Docenza.codiceCorso = NEW.codiceCorso AND Docenza.nomeInsegnante = NEW.insegnanteLezione
    INTO var_docenze ;
    
    IF (var_docenze <> 1) THEN 
		SIGNAL SQLSTATE '45001' SET MESSAGE_TEXT = 'Insegnante NON assegnato al Corso Indicato' ;
	END IF ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezioneCorso_BEFORE_INSERT_2` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezioneCorso_BEFORE_INSERT_2` BEFORE INSERT ON `LezioneCorso` FOR EACH ROW
BEGIN
	## CONTROLLO CONFLITTO DELLA LEZIONE CON ALTRE LEZIONI PRIVATE DI INSEGNANTE
    
    DECLARE var_has_conflict INT DEFAULT 0 ;
    
    SELECT count(*)
    FROM LezionePrivata AS P
    WHERE 
		nomeInsegnante = new.insegnanteLezione 
        AND dataLezione >= NOW() AND
        new.giornoSettimana = conversioneDataGiorno(dataLezione) AND
        NOT verifica_orari_compatibili(new.orarioInizio, new.orarioInizio + INTERVAL new.durata MINUTE, P.orarioLezione, P.orarioLezione + INTERVAL P.durataLezione MINUTE)
	INTO var_has_conflict ;
		
    IF var_has_conflict > 0 THEN 
		SIGNAL SQLSTATE '45006' SET MESSAGE_TEXT = 'Insegnante ha una Lezione Privata in conflitto' ;
    END IF ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezioneCorso_BEFORE_INSERT_3` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezioneCorso_BEFORE_INSERT_3` BEFORE INSERT ON `LezioneCorso` FOR EACH ROW
BEGIN
	DECLARE var_has_conflict INT DEFAULT 0 ;
    
    SELECT count(*)
    FROM LezioneCorso
    WHERE 
		codiceCorso = new.codiceCorso AND
		giornoSettimana = new.giornoSettimana AND
        NOT verifica_orari_compatibili(new.orarioInizio, new.orarioInizio + INTERVAL new.durata MINUTE, orarioInizio, orarioInizio + INTERVAL new.durata MINUTE) 
	INTO var_has_conflict ;
        
	IF var_has_conflict > 0 THEN
		SIGNAL SQLSTATE '45013' SET MESSAGE_TEXT = 'Esiste una lezione del corso in un orario che collide' ;
    END IF ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezionePrivata_BEFORE_INSERT` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezionePrivata_BEFORE_INSERT` BEFORE INSERT ON `LezionePrivata` FOR EACH ROW
BEGIN
	## Controllo NO Conflitto con Lezioni Corso di Insegnante
        
    DECLARE var_has_conflict INT DEFAULT 0 ;
    
    SELECT count(*)
    FROM LezioneCorso
    WHERE 
		insegnanteLezione = new.nomeInsegnante AND 
		giornoSettimana = conversioneDataGiorno(new.dataLezione) AND 
        NOT verifica_orari_compatibili(new.orarioLezione, new.orarioLezione + INTERVAL new.durataLezione MINUTE, orarioInizio, orarioInizio + INTERVAL durata MINUTE) 
    INTO var_has_conflict ;
    
    IF (var_has_conflict <> 0) THEN
		SIGNAL SQLSTATE '45009' SET MESSAGE_TEXT = 'La Lezione Collide Con La Lezione di Qualche Corso' ;
    END IF ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezionePrivata_BEFORE_INSERT_1` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezionePrivata_BEFORE_INSERT_1` BEFORE INSERT ON `LezionePrivata` FOR EACH ROW
BEGIN
    ## Controllo NO Conflitto con Lezioni Private di Insegnante
        
	DECLARE var_has_conflict INT DEFAULT 0 ;
    
    SELECT count(*)
    FROM LezionePrivata
    WHERE 
		dataLezione = new.dataLezione AND
        nomeInsegnante = new.nomeInsegnante AND
		NOT verifica_orari_compatibili(new.orarioLezione, new.orarioLezione + INTERVAL new.durataLezione MINUTE, orarioLezione, orarioLezione + INTERVAL durataLezione MINUTE)
	INTO var_has_conflict ;
    
	IF (var_has_conflict > 0) THEN
		SIGNAL SQLSTATE '45011' SET MESSAGE_TEXT = 'La Lezione Collide Con Altre Lezioni Private Dello Stesso Insegnante' ;
	END IF ;
END$$


USE `my_english_school`$$
DROP TRIGGER IF EXISTS `my_english_school`.`LezionePrivata_BEFORE_INSERT_2` $$
USE `my_english_school`$$
CREATE DEFINER = CURRENT_USER TRIGGER `my_english_school`.`LezionePrivata_BEFORE_INSERT_2` BEFORE INSERT ON `LezionePrivata` FOR EACH ROW
BEGIN
	## Controllo Stesso Studente non ha più lezioni in orari che collidono
    DECLARE var_has_conflict INT DEFAULT 0 ;
    
    ## CONTO IL NUMERO DI LEZIONI CHE COLLIDONO
    SELECT count(*)
    FROM LezionePrivata
    WHERE nomeAllievo = NEW.nomeAllievo AND 
		dataLezione = new.dataLezione AND 
		NOT verifica_orari_compatibili(new.orarioLezione, new.orarioLezione + INTERVAL new.durataLezione MINUTE, orarioLezione, orarioLezione + INTERVAL durataLezione MINUTE) 
    INTO var_has_conflict ;
    
    IF (var_has_conflict > 0) THEN
		SIGNAL SQLSTATE '45007' SET MESSAGE_TEXT = 'Alunno ha già prenotato una lezione in un orario che collide' ;
    END IF ;
END$$


DELIMITER ;
