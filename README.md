# Speden Speli Nopeustesti

Kouluprojekti missä kehiteltiin Arduino R3 kehitysalustalle Speden Spelit -ohjelmasta tuttu "Nopeustesti" peli. 

## Extra ominaisuudet
- Äänet piezo summerin avulla. 
- Parhaimmat 4 tulosta Arduinon EEPROM muistiin. Tulokset näytetään kun peliä ei pelata. 
## Tarvittavat komponentit

- Arduino Uno R3 -alusta
- Neljä LED-valoa 
- Viisi nappia (neljä pelaamiseen, yksi käynnistämiseen)
- 220 ohmin vastuksia LED-valoille
- Kaksi kappaletta 8-bit shift rekistereitä 
- Kaksi kappaletta 7-segment display näyttöjä
- Kytkentälevy
- (Ei pakollinen) Piezo summeri 


## Asennusohjeet

**1. Lataa lähdekoodi**
   - Lataa projektin koodi tämän GitHub-repositorion kautta.

**2. Kytke komponentit**
   - Yhdistä komponentit Arduinoon seuraavan kytkentäkaavion mukaan:
   ![Kuva kytkentä kaaviosta](https://github.com/Skyde789/SpedenSpeli/blob/main/Kaavio.png)

**3. Asenna Arduino IDE**
   - Asenna [Arduino IDE](https://www.arduino.cc/en/software) jos et ole jo sitä asentanut.

**4. Avaa projekti Arduino IDE:ssä**
   - Avaa `SpedenSpelit.ino` Arduino IDE:ssä.
   - Liitä Arduino tietokoneeseen USB-kaapelilla.
   - Valitse oikea portti ja mahdollisesti oikea Arduino malli Arduino IDE:ssä.
   - Lataa koodi Arduinoon klikkaamalla "Upload"-painiketta.

## Käyttöohjeet

**1.** Käynnistä Arduino liittämällä se virtalähteeseen.

**2.** Peli käynnistyy painamalla nappia joka on kytketty pinniin 6.

**3.** Paina oikeaa nappia riippuen siitä mikä LED-valo syttyy.

**4.** Peli loppuu tietyn ajan jälkeen tai jos painat väärää nappia. 

**5.** Parhaat 4 tulosta näytetään 5 sekunnin välein kun peliä ei pelata. 

---

## Tekijät
**1. Koodi**
   - **Game Logic** Sami Laihiainen
   - **Leds**&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sami Laihiainen
   - **Highscore** &nbsp;&nbsp;&nbsp;Sami Laihiainen
   - **Sound** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sami Laihiainen
   - **Buttons** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Oona Kujala
   - **Display** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Niko Laine

**2. Kytkentä** 
  - Niko Laine
  - Oona Kujala

