# include "AIPlayer.h"
# include "../../include/model/Parchis.h"

const float masinf = 9999999999.0, menosinf = -9999999999.0;
const float gana = masinf / 10.f, pierde = menosinf / 10.f;
const int num_pieces = 2;
const int PROFUNDIDAD_MINIMAX = 4; // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
   cout << COUT_ORANGE_BOLD << "Realizo un movimiento automatico" << COUT_NOCOLOR << endl;

   color c_piece;
   int id_piece;
   int dice;
   think(c_piece, id_piece, dice);

   cout << COUT_ORANGE_BOLD << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << COUT_NOCOLOR << endl;

   actual->movePiece(c_piece, id_piece, dice);
   return true;
}

void AIPlayer::think(color& c_piece, int& id_piece, int& dice) const{
   
   // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

   float valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
   float alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
   float umbral_valoracionTest=3.5;
   // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
   ValoracionTest valoracionTest;
   Simple sheur;
   TheBestInMyOpinion thbimpheur;
   GoForNinja1 gfnheur;
   AnotherTry atheur;

   switch(id){
      case 0:
         Poda_Alfa_Beta(*actual, jugador, 0,PROFUNDIDAD_ALFABETA-2, c_piece, id_piece, dice, alpha, beta, &valoracionTest);
      break;
      case 1:
         Poda_Alfa_Beta(*actual, jugador, 0,PROFUNDIDAD_ALFABETA-2, c_piece, id_piece, dice, alpha, beta, &sheur);
      break;
      case 2:
         Poda_Alfa_Beta_Definitiva(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, &thbimpheur);
      break;
      case 3:
         Poda_Alfa_Beta_Definitiva(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, &gfnheur);
      break;
      case 4:
         Poda_Alfa_Beta(*actual, jugador, 0,PROFUNDIDAD_ALFABETA-2, c_piece, id_piece, dice, alpha, beta, &atheur);
      break;
      case 5:
         Poda_Alfa_Beta_Ramificacion(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, &valoracionTest);
      break;
      case 6:
         Poda_Alfa_Beta_Ordenacion(*actual, jugador, 0, PROFUNDIDAD_ALFABETA-4, c_piece, id_piece, dice, alpha, beta, &valoracionTest);
      break;
      case 7:
         Poda_Alfa_Beta_Probabilistica(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, umbral_valoracionTest, &valoracionTest);
      break;
      case 8:
         Poda_Alfa_Beta_Definitiva(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, &valoracionTest);
      break;
      case 9:
         thinkFichaMasAdelantada(c_piece, id_piece, dice);
      break;
      case 10: 
         thinkMejorOpcion(c_piece, id_piece, dice);
      break;
      case 11: 
         Minimax(*actual, jugador, 0, PROFUNDIDAD_MINIMAX, c_piece, id_piece, dice, &valoracionTest);
      break;
      case 12:
         Minimax_Limitado(*actual,jugador,0,PROFUNDIDAD_MINIMAX,c_piece,id_piece,dice,&valoracionTest);
      break;
   }

}


float ValoracionTest::getHeuristic(const Parchis& estado, int jugador) const{
   // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


   int ganador = estado.getWinner();
   int oponente = (jugador + 1) % 2;

   // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
   if (ganador == jugador){
      return gana;
   }
   else if (ganador == oponente){
      return pierde;
   }
   else{
      // Colores que juega mi jugador y colores del oponente
      vector<color> my_colors = estado.getPlayerColors(jugador);
      vector<color> op_colors = estado.getPlayerColors(oponente);

      // Recorro todas las fichas de mi jugador
      int puntuacion_jugador = 0;
      // Recorro colores de mi jugador.
      for (int i = 0; i < my_colors.size(); i++){
         color c = my_colors[i];
         // Recorro las fichas de ese color.
         for (int j = 0; j < num_pieces; j++){
            // Valoro positivamente que la ficha esté en casilla segura o meta.
            if (estado.isSafePiece(c, j)){
               puntuacion_jugador++;
            }
            else if (estado.getBoard().getPiece(c, j).get_box().type == goal){
               puntuacion_jugador += 5;
            }
         }
      }

      // Recorro todas las fichas del oponente
      int puntuacion_oponente = 0;
      // Recorro colores del oponente.
      for (int i = 0; i < op_colors.size(); i++){
         color c = op_colors[i];
         // Recorro las fichas de ese color.
         for (int j = 0; j < num_pieces; j++){
            if (estado.isSafePiece(c, j)){
               // Valoro negativamente que la ficha esté en casilla segura o meta.
               puntuacion_oponente++;
            }
            else if (estado.getBoard().getPiece(c, j).get_box().type == goal){
               puntuacion_oponente += 5;
            }
         }
      }

      // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
      return puntuacion_jugador - puntuacion_oponente;
   }
}

/**************************/
// Metodos del alumno
/**************************/

void AIPlayer::thinkAleatorio(color &c_piece, int &id_piece, int &dice) const{
   // IMPLEMENTACIÓN INICIAL DEL AGENTE
   // Esta implementación realiza un movimiento aleatorio.
   // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente
   //como lo que se muestran al final de la función.

   // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores,
   //respectivamente, de:
   // - color de ficha a mover
   // - identificador de la ficha que se va a mover
   // - valor del dado con el que se va a mover la ficha.

   // El id de mi jugador actual.
   int player = actual->getCurrentPlayerId();

   // Vector que almacenará los dados que se pueden usar para el movimiento
   vector<int> current_dices;
   // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
   vector<tuple<color, int>> current_pieces;

   // Se obtiene el vector de dados que se pueden usar para el movimiento
   current_dices = actual->getAvailableNormalDices(player);
   // Elijo un dado de forma aleatoria.
   dice = current_dices[rand() % current_dices.size()];

   // Se obtiene el vector de fichas que se pueden mover para el dado elegido
   current_pieces = actual->getAvailablePieces(player, dice);

   // Si tengo fichas para el dado elegido muevo una al azar.
   if (current_pieces.size() > 0){
      int random_id = rand() % current_pieces.size();
      id_piece = get<1>(current_pieces[random_id]); // get<i>(tuple<...>) me devuelve el i-ésimo
      c_piece = get<0>(current_pieces[random_id]); // elemento de la tupla
   }
   else{
      // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
      id_piece = SKIP_TURN;
      c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
   }
}

void AIPlayer::thinkFichaMasAdelantada(color &c_piece, int &id_piece, int &dice) const{
   // Elijo el dado haciendo lo mismo que el jugador aleatorio.
   thinkAleatorio(c_piece, id_piece, dice);
   // Tras llamar a esta función, ya tengo en dice el número de dado que quiero usar.
   // Ahora, en vez de mover una ficha al azar, voy a mover (o a aplicar
   // el dado especial a) la que esté más adelantada
   // (equivalentemente, la más cercana a la meta).
   int player = actual->getCurrentPlayerId();
   vector<tuple<color, int>> current_pieces = actual->getAvailablePieces(player, dice);
   int id_ficha_mas_adelantada = -1;
   color col_ficha_mas_adelantada = none;
   int min_distancia_meta = 9999;
   for (int i = 0; i < current_pieces.size(); i++)
   {
      // distanceToGoal(color, id) devuelve la distancia a la meta de la ficha [id] del color que le indique.
      color col = get<0>(current_pieces[i]);
      int id = get<1>(current_pieces[i]);
      int distancia_meta = actual->distanceToGoal(col, id);
      if (distancia_meta < min_distancia_meta)
      {
         min_distancia_meta = distancia_meta;
         id_ficha_mas_adelantada = id;
         col_ficha_mas_adelantada = col;
      }
   }
   // Si no he encontrado ninguna ficha, paso turno.
   if (id_ficha_mas_adelantada == -1)
   {
      id_piece = SKIP_TURN;
      c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
   }
   // En caso contrario, moveré la ficha más adelantada.
   else
   {
      id_piece = id_ficha_mas_adelantada;
      c_piece = col_ficha_mas_adelantada;
   }
}

void AIPlayer::thinkMejorOpcion(color &c_piece, int &id_piece, int &dice) const
{
   // Vamos a mirar todos los posibles movimientos del jugador actual accediendo a los hijos del estado actual.
   // Cuando ya he recorrido todos los hijos, la función devuelve el estado actual. De esta forma puedo saber
   // cuándo paro de iterar.
   // Para ello, vamos a iterar sobre los hijos con la función de Parchis getChildren().
   // Esta función devuelve un objeto de la clase ParchisBros, que es una estructura iterable
   // sobre la que se pueden recorrer todos los hijos del estado sobre el que se llama.
   ParchisBros hijos = actual->getChildren();
   bool me_quedo_con_esta_accion = false;
   // La clase ParchisBros viene con un iterador muy útil y sencillo de usar.
   // Al hacer begin() accedemos al primer hijo de la rama,
   // y cada vez que hagamos ++it saltaremos al siguiente hijo.
   // Comparando con el iterador end() podemos consultar cuándo hemos terminado de visitar los hijos.
   for (ParchisBros::Iterator it = hijos.begin();it != hijos.end() and !me_quedo_con_esta_accion; ++it)
   {
      Parchis siguiente_hijo = *it;
      // Si en el movimiento elegido comiera ficha, llegara a la meta o ganara, me quedo con esa acción.
      // Termino el bucle en este caso.
      if (siguiente_hijo.isEatingMove() or siguiente_hijo.isGoalMove() or (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador))
      {
         me_quedo_con_esta_accion = true;
         c_piece = it.getMovedColor();
         id_piece = it.getMovedPieceId();
         dice = it.getMovedDiceValue();
      }
   }
   // Si he encontrado una acción que me interesa, la guardo en las variables pasadas por referencia.
   // (Ya lo he hecho antes, cuando les he asignado los valores con el iterador).
   // Si no he encontrado ninguna acción que me interese, voy a mover la ficha más adelantada como en el caso
   //anterior.
   if(!me_quedo_con_esta_accion){
      thinkFichaMasAdelantada(c_piece, id_piece, dice);
   }
}

float AIPlayer::Minimax(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, Heuristic *heuristic)const{

   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      // IMPORTANTE: USAMOS EL MÉTODO evaluate AUNQUE HAYAMOS REDEFINIDO LA CLASE HEURISTIC
      return heuristic->evaluate(actual, jugador);
   }
   // Comparo mi jugador con el actual de la partida para saber en qué tipo de nodo estoy
   else if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX
      float valor = menosinf; // Inicialización lo más pequeña posible para ir calculando el máximo
      
      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();

      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Minimax(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece, id_piece, dice,heuristic);
         if (new_val > valor){
            // Me voy quedando con el máximo
            valor = new_val;
            if (profundidad == 0){
            // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }
         }
      }
      return valor;
   }
   else{ // Nodo MIN

      float valor = masinf; // Inicialización lo más grande posible para ir calculando el mínimo

      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();

      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Minimax(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece, id_piece, dice,
         heuristic);
         // Me voy quedando con el mínimo
         if (new_val < valor)
         {
            valor = new_val;
         }
      }
      return valor;
   }
}

float AIPlayer::Minimax_Limitado(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, Heuristic *heuristic)const{
  
   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      // IMPORTANTE: USAMOS EL MÉTODO evaluate AUNQUE HAYAMOS REDEFINIDO LA CLASE HEURISTIC
      return heuristic->evaluate(actual, jugador);
   }
   else if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX
      float valor = menosinf;
      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }
            return valor;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Minimax_Limitado(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,
         id_piece, dice, heuristic);
         if (new_val > valor){
            // Me voy quedando con el máximo
            valor = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }
         }
      }
      return valor;
   }
   else{ // Nodo MIN
      float valor = masinf;
      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Minimax_Limitado(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,
         id_piece, dice, heuristic);
         // Me voy quedando con el mínimo
         if (new_val < valor){
            valor = new_val;
         }
      }
      return valor;
   }
}

float AIPlayer::Poda_Alfa_Beta(const Parchis &actual, int jugador, int profundidad,int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const{
   
   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      return heuristic->evaluate(actual, jugador);
   }
   else if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX

      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }
            return alpha;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice,alpha,beta, heuristic);
         if (new_val > alpha){
            // Me voy quedando con el máximo
            alpha = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }

            if(alpha >= beta){
               // cout << "Podo max" << endl;
               return alpha;
            }
         }
      }
      return alpha;
   }
   else{ // Nodo MIN
      
      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice, alpha,beta,heuristic);
         // Me voy quedando con el mínimo
         if(new_val<beta){
            beta = new_val;
            if(beta<=alpha){
               // cout << "Podo min" << endl;

               return beta;
            }
         }
      }
      return beta;
   }
}

float AIPlayer::Poda_Alfa_Beta_Ramificacion(const Parchis&actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const{
   if (profundidad >= profundidad_max || actual.gameOver()) {
      return heuristic->evaluate(actual, jugador);
  }
  
  // Obtener los hijos del nodo actual
  std::vector<ParchisSis> rama = actual.getChildrenList();
  int ramificacion_actual = rama.size();

  // Calcular profundidad dinámica (asegurando que no exceda profundidad_max)
  int profundidad_siguiente = calcular_profundidad_siguiente(profundidad,profundidad_max,ramificacion_actual);

  cout << "Profundidad siguiente: " << profundidad_siguiente << endl;

   if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX

      //Recorro los hijos
      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;

         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }
            return alpha;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Ramificacion(nuevo_hijo, jugador, profundidad + 1, profundidad_siguiente, c_piece,id_piece, dice,alpha,beta, heuristic);
         if (new_val > alpha){
            // Me voy quedando con el máximo
            alpha = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }

            if(alpha >= beta){
               return alpha;
            }
         }
      }
      return alpha;
   }
   else{ // Nodo MIN

      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Ramificacion(nuevo_hijo, jugador, profundidad + 1, profundidad_siguiente, c_piece,id_piece, dice, alpha,beta,heuristic);
         // Me voy quedando con el mínimo
         if(new_val<beta){
            beta = new_val;
            if(beta<=alpha){
               return beta;
            }
         }
      }
      return beta;
   }
}

float AIPlayer::Poda_Alfa_Beta_Ordenacion(const Parchis &actual, int jugador, int profundidad,int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const{
   
   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      return heuristic->evaluate(actual, jugador);
   }
   std::vector<ParchisSis> rama = actual.getChildrenList();
   if (profundidad == 0) {
      cout << "Ordeno" << endl;
      std::sort(rama.begin(), rama.end(), [&](const ParchisSis &a, const ParchisSis &b) {
         const Parchis& nodoA = *a;
         const Parchis& nodoB = *b;

         float valA = heuristic->evaluate(const_cast<Parchis&>(nodoA), jugador);
         float valB = heuristic->evaluate(const_cast<Parchis&>(nodoB), jugador);

         return valA > valB; // MAX -> mayor primero
      });
      cout << "Ya he ordenado" << endl;
   }
   
   if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX

      // Obtengo los hijos del nodo actual y los recorro
      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }
            return alpha;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Ordenacion(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice,alpha,beta, heuristic);
         if (new_val > alpha){
            // Me voy quedando con el máximo
            alpha = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }

            if(alpha >= beta){
               return alpha;
            }
         }
      }
      return alpha;
   }
   else{ // Nodo MIN
      
      // Obtengo los hijos del nodo actual y los recorro
      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Ordenacion(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice, alpha,beta,heuristic);
         // Me voy quedando con el mínimo
         if(new_val<beta){
            beta = new_val;
            if(beta<=alpha){
               return beta;
            }
         }
      }
      return beta;
   }
}

float AIPlayer::Poda_Alfa_Beta_Probabilistica(const Parchis &actual, int jugador, int profundidad,int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, float umbral,Heuristic *heuristic)const{
   
   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      return heuristic->evaluate(actual, jugador);
   }
   else if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX

      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }
            return alpha;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Probabilistica(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice,alpha,beta, umbral, heuristic);
         if (new_val > alpha){
            // Me voy quedando con el máximo
            alpha = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it.getMovedColor();
               id_piece = it.getMovedPieceId();
               dice = it.getMovedDiceValue();
            }

            if(alpha >= beta or beta-alpha<=umbral){
               cout << "Podo max" << endl;

               return alpha;
            }
         }
      }
      return alpha;
   }
   else{ // Nodo MIN
      
      // Obtengo los hijos del nodo actual y los recorro
      ParchisBros rama = actual.getChildren();
      for (ParchisBros::Iterator it = rama.begin(); it != rama.end(); ++it){
         Parchis nuevo_hijo = *it;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Probabilistica(nuevo_hijo, jugador, profundidad + 1, profundidad_max, c_piece,id_piece, dice, alpha,beta,umbral,heuristic);
         // Me voy quedando con el mínimo
         if(new_val<beta){
            beta = new_val;
            if(beta<=alpha or beta-alpha<=umbral){
               cout << "Podo min" << endl;

               return beta;
            }
         }
      }
      return beta;
   }
}

float AIPlayer::Poda_Alfa_Beta_Definitiva(const Parchis &actual, int jugador, int profundidad,int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const{
   
   if (profundidad == profundidad_max || actual.gameOver()){ // Nodo terminal o profundidad límite: llamo a la función heurística
      // cout << "heuristica" << heuristic->evaluate(actual, jugador) << endl;
      return heuristic->evaluate(actual, jugador);
   }
   std::vector<ParchisSis> rama = actual.getChildrenList();
   int ramificacion_actual = rama.size();
   int profundidad_siguiente = calcular_profundidad_siguiente(profundidad,profundidad_max,ramificacion_actual);

   if (profundidad == 0) {
      // cout << "Ordeno" << endl;
      std::sort(rama.begin(), rama.end(), [&](const ParchisSis &a, const ParchisSis &b) {
         const Parchis& nodoA = *a;
         const Parchis& nodoB = *b;

         float valA = heuristic->evaluate(const_cast<Parchis&>(nodoA), jugador);
         float valB = heuristic->evaluate(const_cast<Parchis&>(nodoB), jugador);

         return valA > valB; // MAX -> mayor primero
      });
      // cout << "Ya he ordenado" << endl;
   }
   
   if (actual.getCurrentPlayerId() == jugador){ // Nodo MAX

      // Obtengo los hijos del nodo actual y los recorro
      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            if(profundidad == 0){
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }
            return alpha;
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Definitiva(nuevo_hijo, jugador, profundidad + 1, profundidad_siguiente, c_piece,id_piece, dice,alpha,beta, heuristic);
         if (new_val > alpha){
            // Me voy quedando con el máximo
            alpha = new_val;
            if (profundidad == 0){
               // Almaceno el movimiento que me ha llevado al mejor valor (solo en la raíz)
               c_piece = it->getMovedColor();
               id_piece = it->getMovedPieceId();
               dice = it->getMovedDiceValue();
            }

            // if(beta-alpha<umbral){
            if(beta<=alpha ){
               // cout << "Podo max" << endl;

               return alpha;
            }
         }
      }
      return alpha;
   }
   else{ // Nodo MIN
      
      // Obtengo los hijos del nodo actual y los recorro
      for ( vector<ParchisSis>::iterator it = rama.begin(); it!=rama.end(); ++it){
         ParchisSis nueva_hija = *it;
         Parchis nuevo_hijo = *nueva_hija;
         // Verificar si hemos alcanzado el límite
         if (NodeCounter::isLimitReached()){
            cout << "Límite de nodos alcanzado, devolviendo el mejor nodo parcial" << endl;
            return heuristic->evaluate(actual, jugador);
         }
         // Búsqueda en profundidad (llamada recursiva)
         float new_val = Poda_Alfa_Beta_Definitiva(nuevo_hijo, jugador, profundidad + 1, profundidad_siguiente, c_piece,id_piece, dice, alpha,beta,heuristic);
         // Me voy quedando con el mínimo
         if(new_val<beta){
            beta = new_val;
            // if(beta-alpha<umbral){
            if(beta<=alpha ){
               // cout << "Podo min" << endl;

               return beta;
            }
         }
      }
      return beta;
   }
}



/******************************/
// Heurísticas
/******************************/

/******************************/
// Simple
/******************************/

float Simple::getHeuristic(const Parchis & estado, int player) const{

   const float ficha_en_meta = 80;         
   const float ficha_alejada = 1.15;
   const float ficha_en_casa = 70;
   const float safe_piece=55;
   const float final_queue_box=82;
   const float blocked = 50;

   int ganador = estado.getWinner();
   int oponent = (player+1)%2;

   if(estado.gameOver()){
      if(ganador==player)
         return gana;
      else if (ganador==oponent)
         return pierde;
   }

   float sum_oponent=0, sum_player=0;

   vector<color> pColors=estado.getPlayerColors(player), oColors = estado.getPlayerColors(oponent);

   //ASPECTOS DE PLAYER
   
   for (int i = 0; i < pColors.size(); i++){
      color c = pColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_player -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_player+=safe_piece;
         if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_player -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_player += final_queue_box;
         else if(BarrierNear(estado,player,c,j,pColors,oColors))
            sum_player -= blocked;
      }
   }

   //ASPECTOS DE OPONENT

   for (int i = 0; i < oColors.size(); i++){
      color c = oColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_oponent -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_oponent+=safe_piece;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_oponent += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_oponent -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_oponent += final_queue_box;  
         else if(BarrierNear(estado,oponent,c,j,oColors,pColors))
            sum_oponent -= blocked;
      }
   }

   return sum_player-sum_oponent;
}

bool Simple::isInDanger(const Parchis & estado, int jugador, color c, int id_piece)const{
   Box pos_ficha = estado.getBoard().getPiece(c, id_piece).get_box();

   if(estado.isSafeBox(pos_ficha))
      return false;
   
   vector <color> oColors = estado.getPlayerColors((jugador+1)%2);

   for(int i=0;i<oColors.size();i++){
      color co = oColors[i];
      for(int j=0; j<num_pieces;j++){
         if(estado.distanceBoxtoBox(co,estado.getBoard().getPiece(co,j).get_box(), pos_ficha)<=10)
            return true;
      } 
   }
   return false;
}

bool Simple::BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier = PiecesinBarriers(estado,pColors,oColors);
   
   if(piecesInBarrier.empty())
      return false;
   
   else{
      for( int i=0; i<piecesInBarrier.size(); i++){
         if(estado.distanceBoxtoBox(c,id_piece,piecesInBarrier[i].first,piecesInBarrier[i].second)==1)
            return true;
      }
   }
   return false;
}

vector<pair<color,int>> Simple::PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier;

   for(int i=0; i<pColors.size(); i++){
      color c=pColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   for(int i=0; i<oColors.size(); i++){
      color c=oColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   return piecesInBarrier;
}

/******************************/
// TheBestInMyOpinion
/******************************/

float TheBestInMyOpinion::getHeuristic(const Parchis & estado, int player) const{
   float ficha_en_meta = 5.5;          
   float ficha_alejada = 1.1;
   float ficha_en_casa = 8.6;
   float safe_piece=7.7;

   int ganador = estado.getWinner();
   int oponent = (player+1)%2;

   if(estado.gameOver()){
      if(ganador==player)
         return gana;
      else if (ganador==oponent)
         return pierde;
   }

   float sum_oponent=0, sum_player=0;

   vector<color> pColors=estado.getPlayerColors(player), oColors = estado.getPlayerColors(oponent);

   //ASPECTOS DE PLAYER
   
   for (int i = 0; i < pColors.size(); i++){
      color c = pColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_player -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         
         if (estado.isSafePiece(c, j))
            sum_player+=safe_piece;
         
         if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_player -= ficha_en_casa; 

         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            sum_player+=safe_piece;
      }
   }

   //ASPECTOS DE OPONENT

   for (int i = 0; i < oColors.size(); i++){
      color c = oColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_oponent -= ficha_alejada*estado.distanceToGoal(c,j);

         if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_oponent+=ficha_en_meta;

         if (estado.isSafePiece(c, j) or estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            sum_oponent+=safe_piece;

         if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_oponent -= ficha_en_casa;

         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            sum_oponent+=safe_piece;
      }
   }


   return sum_player-sum_oponent;
}

/******************************/
// GoForNinja1
/******************************/
float GoForNinja1::getHeuristic(const Parchis & estado, int player) const{

   const float ficha_en_meta = 5.6;          
   const float ficha_alejada = 1.15;
   const float ficha_en_casa = 8.4;
   const float safe_piece=7.84;
   const float final_queue_box=1.15;
   const float blocked = 2.2;

   int ganador = estado.getWinner();
   int oponent = (player+1)%2;

   if(estado.gameOver()){
      if(ganador==player)
         return gana;
      else if (ganador==oponent)
         return pierde;
   }

   float sum_oponent=0, sum_player=0;

   //Premiamos comer una ficha

   int last_player = (estado.getCurrentPlayerId()+1)%2;

   vector<color> pColors=estado.getPlayerColors(player), oColors = estado.getPlayerColors(oponent);

   //ASPECTOS DE PLAYER
   
   for (int i = 0; i < pColors.size(); i++){
      color c = pColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_player -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_player+=safe_piece;
         if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_player -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_player += final_queue_box;
         else if(BarrierNear(estado,player,c,j,pColors,oColors))
            sum_player -= blocked;
      }
   }

   //ASPECTOS DE OPONENT

   for (int i = 0; i < oColors.size(); i++){
      color c = oColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_oponent -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_oponent+=safe_piece;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_oponent += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_oponent -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_oponent += final_queue_box;  
         else if(BarrierNear(estado,oponent,c,j,oColors,pColors))
            sum_oponent -= blocked;
      }
   }

   return sum_player-sum_oponent;
}

bool GoForNinja1::BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier = PiecesinBarriers(estado,pColors,oColors);
   
   if(piecesInBarrier.empty())
      return false;
   
   else{
      for( int i=0; i<piecesInBarrier.size(); i++){
         if(estado.distanceBoxtoBox(c,id_piece,piecesInBarrier[i].first,piecesInBarrier[i].second)==1)
            return true;
      }
   }
   return false;
}

vector<pair<color,int>> GoForNinja1::PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier;

   for(int i=0; i<pColors.size(); i++){
      color c=pColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   for(int i=0; i<oColors.size(); i++){
      color c=oColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   return piecesInBarrier;
}

/******************************/
// AnotherTry
/******************************/

float AnotherTry::getHeuristic(const Parchis & estado, int player) const{

   const float ficha_en_meta = 80;         
   const float ficha_alejada = 1.15;
   const float ficha_en_casa = 70;
   const float safe_piece=57;
   const float final_queue_box=82;
   const float blocked = 62;

   int ganador = estado.getWinner();
   int oponent = (player+1)%2;

   if(estado.gameOver()){
      if(ganador==player)
         return gana;
      else if (ganador==oponent)
         return pierde;
   }

   float sum_oponent=0, sum_player=0;

   //Premiamos comer una ficha

   int last_player = (estado.getCurrentPlayerId()+1)%2;

   vector<color> pColors=estado.getPlayerColors(player), oColors = estado.getPlayerColors(oponent);

   //ASPECTOS DE PLAYER
   
   for (int i = 0; i < pColors.size(); i++){
      color c = pColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_player -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_player+=safe_piece;
         if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_player += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_player -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_player += final_queue_box;
         else if(BarrierNear(estado,player,c,j,pColors,oColors))
            sum_player -= blocked;
      }
   }

   //ASPECTOS DE OPONENT

   for (int i = 0; i < oColors.size(); i++){
      color c = oColors[i];

      for (int j = 0; j < num_pieces; j++){
         
         sum_oponent -= ficha_alejada*estado.distanceToGoal(c,j);
         
         if (estado.isSafePiece(c, j))
            sum_oponent+=safe_piece;
         else if(estado.getBoard().getPiece(c, j).get_box().type == goal)
            sum_oponent += ficha_en_meta;
         else if(estado.getBoard().getPiece(c, j).get_box().type == home)
            sum_oponent -= ficha_en_casa; 
         else if(estado.getBoard().getPiece(c, j).get_box().type == final_queue)
            sum_oponent += final_queue_box;  
         else if(BarrierNear(estado,oponent,c,j,oColors,pColors))
            sum_oponent -= blocked;
      }
   }


   return sum_player-sum_oponent;
}

bool AnotherTry::BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier = PiecesinBarriers(estado,pColors,oColors);
   
   if(piecesInBarrier.empty())
      return false;
   
   else{
      for( int i=0; i<piecesInBarrier.size(); i++){
         if(estado.distanceBoxtoBox(c,id_piece,piecesInBarrier[i].first,piecesInBarrier[i].second)==1)
            return true;
      }
   }
   return false;
}

vector<pair<color,int>> AnotherTry::PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const{
   vector<pair<color,int>> piecesInBarrier;

   for(int i=0; i<pColors.size(); i++){
      color c=pColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   for(int i=0; i<oColors.size(); i++){
      color c=oColors[i];
      for(int j=0; j<num_pieces; j++){
         if(estado.isWall(estado.getBoard().getPiece(c,j).get_box()))
            piecesInBarrier.push_back(make_pair(c,j));
      }
   }

   return piecesInBarrier;
}


/******************************/
// Metodos auxiliares
/******************************/

int AIPlayer::calcular_profundidad_siguiente(int profundidad, int profundidad_max, int ramificacion_actual) const {
   // Caso base: siempre avanzar al menos 1 nivel
   if (profundidad >= profundidad_max) return profundidad;

   // Evita valores negativos o 0
   ramificacion_actual = std::max(1, ramificacion_actual);

   int factor_reduccion = min(8, max(1, 8 - ramificacion_actual));

   int incremento = min(10, factor_reduccion);
   
   int profundidad_siguiente = profundidad + incremento;
   // Cálculo final con límites razonables
   return min(profundidad_siguiente, profundidad + 20);
}

/******************************/
// No usadas
/******************************/

pair<color,int> PieceWithMinDistanceToGoal(const Parchis & estado, int jugador,const vector<color> & my_colors){
   int min_dist=999999;
   pair<color,int> ficha=make_pair(my_colors[0],0);

   int distance=0;
   for (int i = 0; i < my_colors.size(); i++){
      // Recorro las fichas de ese color.
      for (int j = 0; j < num_pieces; j++){
         distance=estado.distanceToGoal(my_colors[i],j);
         if(distance<min_dist){
            min_dist=distance;
            ficha=make_pair(my_colors[i],j);
         }
                    
      }
   }

   return ficha;
}

pair<color,int> PieceWithMaxDistanceToGoal(const Parchis & estado, int jugador,const vector<color> & my_colors){
   int max_dist=-1;
   pair<color,int> ficha=make_pair(my_colors[0],0);

   int distance=0;
   for (int i = 0; i < my_colors.size(); i++){
      // Recorro las fichas de ese color.
      for (int j = 0; j < num_pieces; j++){
         distance=estado.distanceToGoal(my_colors[i],j);
         if(distance>max_dist){
            max_dist=distance;
            ficha=make_pair(my_colors[i],j);
         } 
      }
   }

   return ficha;

}

int getMaxDistanceBetweenPieces(const Parchis & estado, int jugador){

   vector<color> my_colors = estado.getPlayerColors(jugador);

   pair<color,int> min_ficha=PieceWithMinDistanceToGoal(estado, jugador, my_colors);
   pair<color,int> max_ficha=PieceWithMaxDistanceToGoal(estado, jugador, my_colors);
   
   return estado.distanceToGoal(max_ficha.first,max_ficha.second)-estado.distanceToGoal(min_ficha.first,min_ficha.second);

   //Se podría hacer con distanceBoxtoBox pero habría muchas mas llamadas de funciones -> creo que bajaría la eficiencia.
}

int getNumPiecesThreatened(const Parchis & estado,int jugador, const vector<color> &player_colors, const vector<color> &oponent_colors){
   vector<Box> player_boxes={estado.getBoard().getPiece(player_colors[0], 0).get_box(),estado.getBoard().getPiece(player_colors[0], 1).get_box(),
                             estado.getBoard().getPiece(player_colors[1], 0).get_box(),estado.getBoard().getPiece(player_colors[1], 1).get_box()};

   vector<Box> oponent_boxes={estado.getBoard().getPiece(oponent_colors[0], 0).get_box(),estado.getBoard().getPiece(oponent_colors[0], 1).get_box(),
                             estado.getBoard().getPiece(oponent_colors[1], 0).get_box(),estado.getBoard().getPiece(oponent_colors[1], 1).get_box()};

   int counter=0;
   color c;
   for( int i=0; i<player_boxes.size(); i++){
      
      for(int j=0; j<oponent_boxes.size();j++){
         if(j==0 or j==1)
            c = oponent_colors[0];
         else 
            c = oponent_colors[1];
         
         int distance=estado.distanceBoxtoBox(c,oponent_boxes[j],player_boxes[i]);
         if(distance<=6)
            counter++;
      }
   }

   //!Puede que tenga que comprobar los dados
                
   return counter;
}

int getNumPiecesInBarrier(const Parchis &estado,int jugador){

   vector<color> my_colors = estado.getPlayerColors(jugador);

   int counter=0;
      for (int i = 0; i < my_colors.size(); i++){
         // Recorro las fichas de ese color.
         for (int j = 0; j < num_pieces; j++){
            
               if(estado.isWall(estado.getBoard().getPiece(my_colors[i], j).get_box()))
                  counter++;        
         }
      }
   return counter/2;
}



















