meanBorrowedBook <- function(nothing) {
  #db_user='legerant', db_password='Tarzan225', db_name='biblio', db_host='localhost'
  #Installer et charger la librairie RMySQL pour communiquer avec la base de données
  library(RMySQL)
  
  #Utiliser la fonction dbConnect() pour établir la connexion avec la BD
  mydb = dbConnect(MySQL(), user='legerant', password='Tarzan225', dbname='biblio', host='localhost')
  
  #Les requêtes peuvent être éxecuté en utilisant la fonction dbSendQuery()
  #Nous enregistrons le résultat dans la variable results
  results = dbSendQuery(mydb, "select year(b.out_date), month(b.out_date), count(*) per_month from adherents a, borrowings b  where b.adherent_number = a.number group by year(out_date), month(out_date)")
  
  #Pour avoir accès aux résultats dans l'environnement R, on utilise la fonction fetch()
  #Qui save les resulats comme un obbjet dataframe 
  data = dbFetch(results, n=-1)
  
  return(mean(data$per_month))
} 

