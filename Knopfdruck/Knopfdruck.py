# !/usr/bin/python
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import sqlite3
import time

class MyClient():
    def __init__(self, BROKER_ADDRESS="deineBrokerIP", PORT=1883, TOPIC='home/data',QOS=2):
        self.BROKER_ADDRESS = BROKER_ADDRESS
        self.PORT = PORT
        self.QOS = QOS
        self.TOPIC = TOPIC
        self.client = mqtt.Client(client_id="esp32-client-", clean_session=False)
        self.verbindeDb('dein_pfad_zur_datei') 
        
        def on_message(client, userdata, message):
            msg = str(message.payload.decode("utf-8"))
            print(msg)
            msgList = msg.split(':')
            t_id = msgList[1]
            farb_id = msgList[2]
            zeit = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()) #Timestamp erstellen
            
            cmd = "INSERT INTO vorgaenge (toiletten_ID, timestamp, toilettenpapier_art_ID) VALUES ('"+t_id+"', '"+zeit+"', '"+farb_id+"')" 

            print(cmd)
            self.cursor.execute(cmd)
            self.connection.commit()
    
        self.client.on_message = on_message
        
    def verbindeDb(self, filename):
        self.connection = sqlite3.connect(filename)
        self.cursor = self.connection.cursor()

        cmd = """
              CREATE TABLE IF NOT EXISTS toiletten (
              toiletten_ID INTEGER PRIMARY KEY AUTOINCREMENT,
              geschlecht VARCHAR(10)
              )
            """ 
        self.cursor.execute(cmd)
        self.connection.commit()

        cmd = """
            CREATE TABLE IF NOT EXISTS toilettenpapierart (
            toilettenpapier_art_ID INTEGER PRIMARY KEY AUTOINCREMENT,
            farb_id VARCHAR(5),
            beschreibung VARCHAR(100)
            )
            """
        self.cursor.execute(cmd)
        self.connection.commit()
        
        cmd = """
                CREATE TABLE IF NOT EXISTS vorgaenge (
                vorgangs_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                toiletten_ID VARCHAR(2),
                timestamp VARCHAR(50),
                toilettenpapier_art_ID INTEGER
                )
              """
        self.cursor.execute(cmd)
        self.connection.commit()
        
    
    def connect(self):
        self.client.connect(self.BROKER_ADDRESS, self.PORT)
        
    def subscribe(self):
        self.client.subscribe(self.TOPIC, qos=self.QOS)
        print("Connected to MQTT Broker: " + self.BROKER_ADDRESS)
        self.client.loop_forever()


if __name__ == "__main__":
    myClient = MyClient()
    myClient.connect()
    myClient.subscribe()
   




    
