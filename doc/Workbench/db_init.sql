## Livello
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Elementary", "Get Insight - Elementary", 0) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Pre Intermediate", "Get Insight - Pre Intermediate", 0) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Intermediate", "Get Insight - Intermediate", 1) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Pre Advanced", "Get Insight - Pre Advanced", 1) ;
INSERT INTO Livello(nomeLivello, libro, esame) VALUES("Advanced", "Get Insight - Advanced", 1) ;


## Corso
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (8, "Elementary", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (9, "Elementary", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (10, "Pre Intermediate", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (11, "Intermediate", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (12, "Pre Advanced", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (13, "Advanced", NOW(), DEFAULT) ;
INSERT INTO Corso(codiceCorso, nomeLivello, dataAttivazione, numeroAllievi) VALUES (14, "Advanced", NOW(), DEFAULT) ;

## Utenti
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("cercei.lannister", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("jon.snow", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("sansa.stark", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("arya.stark", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("catelyn.tully", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("tyrion.lannister", "ins", "insegnante") ;
INSERT INTO Utenti(username, `password`, ruolo ) VALUES("daenerys.targaryen", "ins", "insegnante") ;
    
## Insegnante
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Cercei Lannister", "Westeros", "Approdo Del Re, Fortezza Rossa", "cercei.lannister") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Jon Snow", "Westeros", "Barriera", "jon.snow") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Sansa Stark", "Westeros", "Grande Inverno", "sansa.stark") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Arya Stark", "Westeros", "Bravos", "arya.stark") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Catelyn Tully", "Westeros", "Delta delle Acque", "catelyn.tully") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Tyrion Lannister", "Westeros", "Castel Granito", "tyrion.lannister") ;
INSERT INTO Insegnante(nomeInsegnante, nazioneInsegnante, indirizzoInsegnante, username) VALUES ("Daenerys Targaryen", "Westeros", "Astapor", "daenerys.targaryen") ;

## Docenze
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (8, "Elementary", "Cercei Lannister") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (8, "Elementary", "Jon Snow") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (9, "Elementary", "Jon Snow") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (9, "Elementary", "Arya Stark") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (10, "Pre Intermediate", "Daenerys Targaryen") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (11, "Intermediate", "Tyrion Lannister") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (12, "Pre Advanced", "Cercei Lannister") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (13, "Advanced", "Jon Snow") ;
INSERT INTO Docenza(codiceCorso, livelloCorso, nomeInsegnante) VALUES (13, "Advanced", "Catelyn Tully") ;

## Lezione Corso
INSERT INTO LezioneCorso(giornoSettimana, orarioInizio, codiceCorso, livelloCorso, durata, insegnanteLezione) VALUES ('Lun', '09:00:00', 8, "Elementary", 60, "Cercei Lannister") ;
INSERT INTO LezioneCorso(giornoSettimana, orarioInizio, codiceCorso, livelloCorso, durata, insegnanteLezione) VALUES ('Lun', '12:30:00', 8, "Elementary", 90, "Cercei Lannister") ;
INSERT INTO LezioneCorso(giornoSettimana, orarioInizio, codiceCorso, livelloCorso, durata, insegnanteLezione) VALUES ('Mar', '10:30:00', 12, "Pre Advanced", 60, "Cercei Lannister") ;
INSERT INTO LezioneCorso(giornoSettimana, orarioInizio, codiceCorso, livelloCorso, durata, insegnanteLezione) VALUES ('Mer', '15:30:00', 12, "Pre Advanced", 75, "Cercei Lannister") ;
INSERT INTO LezioneCorso(giornoSettimana, orarioInizio, codiceCorso, livelloCorso, durata, insegnanteLezione) VALUES ('Dom', '15:30:00', 12, "Pre Advanced", 75, "Cercei Lannister") ;

## Allievo
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Bart Simpson", "3314182627", DEFAULT, NOW(), 8, "Elementary") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Homer Simpson", "3314182627", DEFAULT, NOW(), 8, "Elementary") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Marge Simpson", "3314182627", DEFAULT, NOW(), 9, "Elementary") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Lisa Simpson", "3314182627", DEFAULT, NOW(), 10, "Pre Intermediate") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Maggie Simpson", "3314182627", DEFAULT, NOW(), 10, "Pre Intermediate") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Morgana", "3314182627", DEFAULT, NOW(), 11, "Intermediate") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Artù", "3314182627", DEFAULT, NOW(), 12, "Pre Advanced") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Viviana", "3314182627", DEFAULT, NOW(), 13, "Advanced") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Lancillotto", "3314182627", DEFAULT, NOW(), 13, "Advanced") ;
INSERT INTO Allievo(nomeAllievo, telefonoAllievo, numeroAssenze, dataIscrizione, codiceCorso, livelloCorso) VALUES ("Ginevra", "3314182627", DEFAULT, NOW(), 13, "Advanced") ;


## LezionePrivata
INSERT INTO LezionePrivata VALUES (NOW(), NOW(), "Cercei Lannister", 45, "Bart Simpson") ;
INSERT INTO LezionePrivata VALUES (NOW() + INTERVAL 1 DAY, NOW(), "Cercei Lannister", 45, "Bart Simpson") ;

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