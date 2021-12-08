# Projet Final
### Date: 9 novembre 2021

#### Auteur

- Jamesley Joseph

- Philip Hadjis

- Mathieu Benoit

- Nina Lounici

  

# Parcours

  

    1. attende
    1.A attendre
    
    1.B avancer jusqu'a 12 pouce mur (suivre ligne noit)
    
    1.C attente
    
    1.D 180 degre
    
    2. faire Boucle C, B, G, H, C, B, G, F
	 2.a Hardcode ligne jaune
    
    3. Poteau
    
    3.A Faire Virage 90deg
    
    3.B arret poteau 12-po
    
    3.B.1 Affichage distance
    
    3.C Contournement Poteau
    
    4. Mur 2
    
    5. Position finale

  

# Classes

### Can

- Classe qui permet convertir un signal analogique en données numériques

-Ex: uint8_t lecture = can.lecture(PA0) >> 2;

### Conducteur

- Classe principal du robot qui permet de gérer les états du robot et d'executer des mouvements.

- Contient les méthodes suivreLigne qui permet de suivre une ligne ne utilisant le capteur et qui permet de faire des changements au PWM.

- Cette class contient aussi les états de enableMoteur et affichageDistance.

### LCM

- Classe qui permet d'afficher du texte sur le LCD.

  

### Distance

- Classe qui permet permet de lire une distance avec le capteur infrarouge.

- La méthodeLire distance convertie utilise le CAN pour convertir une valeur analogique en numérique

pour ensuite en utilisant une fonction de calibration caluler une distance à partir d'un voltage.

  

### Minuterie

- Classe qui permet de démaré une minuterie par interruption en ajustant les registres appropriés.

  

### Sonore

- Classe qui permet d'ajuster les registres appropriées afin d'utilisé le Piézo en PWM afin de générer une fréquence.

  

# Liste des Port

  

    PA0: IR ligne #1
    
    PA1: IR ligne #2
    
    PA2: IR ligne #3
    
    PA3: IR ligne #4
    
    PA4: IR ligne #5
    
    PA5: IR calibration
    
    PA6: IR distance
    
    PA7: LED -
    
    VCC: IR ligne VCC
    
    GND: IR ligne VCC
    
    
    
    PB0: LED +
    
    PB1: LED -
    
    PB2:
    
    PB3: Sonore
    
    PB4:
    
    PB5: Sonore
    
    PB6:
    
    PB7:
    
    VCC: IR Distance VCC
    
    GND: IR Distance GND
    
    
    
    PC0: LCD
    
    PC1: LCD
    
    PC2: LCD
    
    PC3: LCD
    
    PC4: LCD
    
    PC5: LCD
    
    PC6: LCD
    
    PC7: LCD
    
    VCC: LCD VCC
    
    GND: LCD GND
    
    
    
    PD0
    
    PD1
    
    PD2: Bouton interupt carte mère INT0
    
    PD3: Bouton interupt breadboard INT1
    
    PD4: PWM Rouge Gauche(E)
    
    PD5: PWM Roue Droite (E)
    
    PD6: Direction Roue Gauche (D)
    
    PD7: Direction Roue Droite (D)
    
    VCC: Button poussoir VCC
    
    GND: Button poussoir GND