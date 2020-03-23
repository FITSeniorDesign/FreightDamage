import sqlite3
from sqlite3 import Error
 
 
def create_connection(db_file):
    """ create a database connection to a SQLite database """
    print "HERE"
    conn = None
    try:
        connection = sqlite3.connect(db_file)
        cursor = connection.cursor()
        results = cursor.execute("SELECT * FROM FragilityTable;")
        for r in results:
            print (r)
        cursor.close()
        connection.close()
    except Error as e:
        print(e)
    finally:
        if conn:
            conn.close()
 
 
if __name__ == '__main__':
    print("I am here!!");
    create_connection(r"C:\Users\elcha\Documents\dbFolder\fragilityDB.db")      # This is my path... need to incorporate