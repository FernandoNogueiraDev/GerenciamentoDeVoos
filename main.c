#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main()
{
  MYSQL *conn = mysql_init(NULL);

  if (mysql_real_connect(conn, "localhost", "root", "",
          NULL, 3306, NULL, 0) == NULL)
  {
      printf("Erro na conexão! \n");
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
  }

  if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS Aeroporto"))
  {
      printf("Erro criação do banco! \n");
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
  }

  if(mysql_query(conn, "USE Aeroporto"))
    {
       printf("Erro utilização do banco Aeroporto! \n");
       fprintf(stderr, "%s\n", mysql_error(conn));
       mysql_close(conn);
       exit(1);

    }



    if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS Aviao(idTeste INT PRIMARY KEY AUTO_INCREMENT, destino varchar(20) NOT NULL, numeroPassageiros int)"))
    {
       printf("Erro criação da tabela Aviao! \n");
       fprintf(stderr, "%s\n", mysql_error(conn));
       mysql_close(conn);
       exit(1);

    }

  printf("Sucesso! \n");
  mysql_close(conn);
  exit(0);


  return 0;
}
