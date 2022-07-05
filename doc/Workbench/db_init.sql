## Livello
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Elementary", "Get Insight - Elementary", 0) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Pre Intermediate", "Get Insight - Pre Intermediate", 0) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Intermediate", "Get Insight - Intermediate", 1) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Pre Advanced", "Get Insight - Pre Advanced", 1) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Advanced", "Get Insight - Advanced", 1) ;


## Corso
INSERT INTO Corso VALUES (8, "Elementary", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (9, "Elementary", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (10, "Pre Intermediate", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (11, "Intermediate", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (12, "Pre Advanced", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (13, "Advanced", NOW(), DEFAULT) ;
INSERT INTO Corso VALUES (14, "Advanced", NOW(), DEFAULT) ;

## Utenti
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("cercei.lannister", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("jon.snow", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("sansa.stark", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("arya.stark", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("catelyn.tully", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("tyrion.lannister", sha1('insegnante'), "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("daenerys.targaryen", sha1('insegnante'), "insegnante") ;
    
## Insegnante
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Cercei Lannister", "Westeros", "Approdo Del Re, Fortezza Rossa", "cercei.lannister") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Jon Snow", "Westeros", "Barriera", "jon.snow") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Sansa Stark", "Westeros", "Grande Inverno", "sansa.stark") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Arya Stark", "Westeros", "Bravos", "arya.stark") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Catelyn Tully", "Westeros", "Delta delle Acque", "catelyn.tully") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Tyrion Lannister", "Westeros", "Castel Granito", "tyrion.lannister") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Daenerys Targaryen", "Westeros", "Astapor", "daenerys.targaryen") ;

## Docenze
INSERT INTO Docenza VALUES (8, "Cercei Lannister") ;
INSERT INTO Docenza VALUES (8, "Jon Snow") ;
INSERT INTO Docenza VALUES (9, "Jon Snow") ;
INSERT INTO Docenza VALUES (9, "Arya Stark") ;
INSERT INTO Docenza VALUES (10, "Daenerys Targaryen") ;
INSERT INTO Docenza VALUES (11,  "Tyrion Lannister") ;
INSERT INTO Docenza VALUES (12,  "Cercei Lannister") ;
INSERT INTO Docenza VALUES (13,  "Jon Snow") ;
INSERT INTO Docenza VALUES (13, "Catelyn Tully") ;

## Lezione Corso
INSERT INTO LezioneCorso VALUES ('Lun', '09:00:00', 8, 60, "Cercei Lannister") ;
INSERT INTO LezioneCorso VALUES ('Lun', '12:30:00', 8, 90, "Cercei Lannister") ;
INSERT INTO LezioneCorso VALUES ('Mar', '10:30:00', 12, 60, "Cercei Lannister") ;
INSERT INTO LezioneCorso VALUES ('Mer', '15:30:00', 12, 75, "Cercei Lannister") ;
INSERT INTO LezioneCorso VALUES ('Dom', '15:30:00', 12, 75, "Cercei Lannister") ;

## Allievo
INSERT INTO Allievo VALUES ("Bart Simpson", "3314182627", DEFAULT, NOW(), 8) ;
INSERT INTO Allievo VALUES ("Homer Simpson", "3314182627", DEFAULT, NOW(), 8) ;
INSERT INTO Allievo VALUES ("Marge Simpson", "3314182627", DEFAULT, NOW(), 9) ;
INSERT INTO Allievo VALUES ("Lisa Simpson", "3314182627", DEFAULT, NOW(), 10) ;
INSERT INTO Allievo VALUES ("Maggie Simpson", "3314182627", DEFAULT, NOW(), 10) ;
INSERT INTO Allievo VALUES ("Morgana", "3314182627", DEFAULT, NOW(), 11) ;
INSERT INTO Allievo VALUES ("Artù", "3314182627", DEFAULT, NOW(), 12) ;
INSERT INTO Allievo VALUES ("Viviana", "3314182627", DEFAULT, NOW(), 13) ;
INSERT INTO Allievo VALUES ("Lancillotto", "3314182627", DEFAULT, NOW(), 13) ;
INSERT INTO Allievo VALUES ("Ginevra", "3314182627", DEFAULT, NOW(), 13) ;


## LezionePrivata
INSERT INTO LezionePrivata VALUES (NOW() - INTERVAL 2 DAY, NOW(), 'Cercei Lannister', 60, "Lancillotto") ;
INSERT INTO LezionePrivata VALUES (NOW(), NOW(), "Cercei Lannister", 45, "Bart Simpson") ;
INSERT INTO LezionePrivata VALUES (NOW() + INTERVAL 1 DAY, NOW(), "Cercei Lannister", 45, "Bart Simpson") ;
INSERT INTO LezionePrivata VALUES (NOW() + INTERVAL 4 DAY, NOW(), "Cercei Lannister", 60, "Marge Simpson") ;

## Attività
INSERT INTO AttivitaCulturale VALUES (100, '2022-09-23', '09:00', 0, 'Animali Fantastici, Dove Trovarli', 'Non Lo So', NULL, NULL) ;
INSERT INTO AttivitaCulturale VALUES (101, '2022-09-23', '09:00', 0, 'Animali Fantastici, I Crimini Di Grinderwald', 'Non Lo So', NULL, NULL) ;
INSERT INTO AttivitaCulturale VALUES (102, '2022-09-23', '09:00', 0, 'Animali Fantastici, I Segreti di Silente', 'Non Lo So', NULL, NULL) ;
INSERT INTO AttivitaCulturale VALUES (103, '2022-09-23', '09:00', 1, NULL, NULL, 'Conferenza 1', 'Argomento 1') ;
INSERT INTO AttivitaCulturale VALUES (104, '2022-09-23', '09:00', 1, NULL, NULL, 'Conferenza 2', 'Argomento 2') ;
INSERT INTO AttivitaCulturale VALUES (105, '2022-09-23', '09:00', 1, NULL, NULL, 'Conferenza 3', 'Argomento 3') ;
INSERT INTO AttivitaCulturale VALUES (106, '2022-09-23', '09:00', 1, NULL, NULL, 'Conferenza 4', 'Argomento 4') ;


## Partecipazione
INSERT INTO Partecipazione VALUES(100, 'Bart Simpson') ;
INSERT INTO Partecipazione VALUES(100, 'Lancillotto') ;
INSERT INTO Partecipazione VALUES(100, 'Ginevra') ;
INSERT INTO Partecipazione VALUES(101, 'Homer Simpson') ;
INSERT INTO Partecipazione VALUES(101, 'Morgana') ;
INSERT INTO Partecipazione VALUES(102, 'Viviana') ;
INSERT INTO Partecipazione VALUES(102, 'Maggie Simpson') ;