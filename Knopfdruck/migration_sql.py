import sqlite3

cmdList = []
connection = sqlite3.connect('deinPfadZurDatenbank')
cursor = connection.cursor()
cmd = """
    ALTER TABLE vorgaenge
    ADD toilettenpapier_art_ID INTEGER
    """
cmdList.append(cmd)
cmd = """
              CREATE TABLE IF NOT EXISTS toiletten (
              toiletten_ID INTEGER PRIMARY KEY AUTOINCREMENT,
              geschlecht VARCHAR(10)
              )
            """
cmdList.append(cmd)
cmd = """
            CREATE TABLE IF NOT EXISTS toilettenpapierart (
            toilettenpapier_art_ID INTEGER PRIMARY KEY AUTOINCREMENT,
            farb_id VARCHAR(5),
            beschreibung VARCHAR(100)
            )
            """
cmdList.append(cmd)
cmd = "INSERT INTO toiletten (toiletten_ID, geschlecht) VALUES (1, 'm')"
cmdList.append(cmd)
cmd = "INSERT INTO toilettenpapierart (toilettenpapier_art_ID, farb_id, beschreibung) VALUES (0, 'weiss', 'Weisses Toilettenpapier')"
cmdList.append(cmd)
cmd = "INSERT INTO toilettenpapierart (toilettenpapier_art_ID, farb_id, beschreibung) VALUES (1, 'rot', 'Rotes Toilettenpapier')"
cmdList.append(cmd)
cmd = "INSERT INTO toilettenpapierart (toilettenpapier_art_ID, farb_id, beschreibung) VALUES (2, 'blau', 'Blaues Toilettenpapier')"
cmdList.append(cmd)
cmd = "INSERT INTO toilettenpapierart (toilettenpapier_art_ID, farb_id, beschreibung) VALUES (3, 'gruen', 'Gruenes Toilettenpapier')"
cmdList.append(cmd)

for cmd in cmdList:
    cursor.execute(cmd)
    connection.commit()
