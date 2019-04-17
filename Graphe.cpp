#include "Graphe.h"
#include "main.h"

Coord::Coord(short x, short y): m_x{x} , m_y {y}
{
	//std::cout << "(" + x << ";" << y + ")" << std::endl;
}

short Coord::get_x() const
{
	return m_x;
}

short Coord::get_y() const
{
	return m_y;
}

Coord::~Coord()
{

}




	//------------------GRAPH------------------
	Graph::Graph(std::string _FileName)
	{
		std::string value;
		std::ifstream file1{ _FileName + ".txt" };		//Ouvre le fichier .txt demand�
		std::cout << "Quelle chiffre de fichier?";
		std::cin >> value;								//On choisit ici quel fichier d epoids on veut ouvrir avec
		std::ifstream file2{ _FileName + "_weights_" + value +".txt" };	//Ouverture du fichier cit� au dessus
		if (!file1 || !file2)
			throw std::runtime_error("Impossible d'ouvrir en lecture " + _FileName +".txt ou "+ _FileName + "_weights_" + value + ".txt");	//lance une erreur si le fichier ne peux pas s'ouvrir car n'existe pas
		if (file1.fail() || file2.fail())
			throw std::runtime_error("Probleme lecture ordre du graphe");

		//Cr�ation des variables necessaire � la r�cup�ration des coordonn�es
		unsigned int NbPoints;
		short x=0;
		short y=0;
		std::string id;
		file1 >> NbPoints;


		//cr�ation des sommets avec Coords///
		for (unsigned int i = 0; i < NbPoints; i++) //Tant que tous les points ne sont pas ajout�s
		{
			file1 >> id; if (file1.fail()) throw std::runtime_error("Probleme de lecture des donn�es");
			file1 >> x; if (file1.fail()) throw std::runtime_error("Probleme de lecture des donn�es");
			file1 >> y; if (file1.fail()) throw std::runtime_error("Probleme de lecture des donn�es");
			std::cout << x << " " << y << "--------------";
			m_points.insert({ id, new Point(id, x,y ) });
		}
		//D�claration des variables n�cessaire � la cr�ation des arr�tes//
		unsigned int NbLinks;
		unsigned int NbLinks2;
		float weight1;
		float weight2;
		std::string id_A;
		std::string id_B;
		file1 >> NbLinks;
		file2 >> NbLinks2;
		file2 >> id;

		if (NbLinks != NbLinks2)//Si le nombre d'arr�te du fichier 1 et 2 sont diff�rentes alors on lance une erreur
			throw std::runtime_error("Nombre d'arrete diff�rents dans les fichiers");
		for (unsigned int i = 0; i < NbLinks; i++)
		{
			file1 >> id; file2 >> id;//Trouver moyen de passer directement � la suite//
			file1 >> id_A;//On r�cup�re l'id du point de d�part
			file1 >> id_B;//On r�cup�re l'id du point de destination
			file2 >> weight1;//On r�cup�re dans le deuxi�me fichier le premier poids
			file2 >> weight2;//puis le deuxi�me
			/*
				Calcul avec la diff�rence des coord id_A et id_B lpour avoir coord_text

				Recherche du mode de l'arr�te:
					x_a=x_b => vertical , y_a=y_b=> horizontal
				sinon
					si x_a<x_b et y_a<y_b ou x_b<x_a et y_b<y_a
						alors
							mode='l'
					sinon si x_a>x_b et y_a<y_b ou x_b>x_a et y_b<y_a
						alors
							mode='r'
			*/
			Link* ptLink = new Link(id, weight1, weight2, id_A, id_B);
			m_links.insert({ id, ptLink  }); //On aoute toutes les valeurs r�cup�rer sur l'arr�te dans la map comprise dans le graphe

			//Ajout des voisins dans les donn�es des points
			(m_points.find(id_A))->second->addNeighboor(ptLink, id_B);//Ajout de la liaison entre A et B
			(m_points.find(id_B))->second->addNeighboor(ptLink, id_A);//Ajout de la liaison entre B et A
		}
		//Ajout des extr�mit�s des arr�tes//
		//Relecture du nombre d'arr�tes//
		//Lecture du nombre de poids � prendre en compte (premier test avec 2 non dynamique)//
		//Ajout pour id du nombre cost1 et cost2//
		file1.close();
		file2.close();

	}


		//A REMETTRE
	/*void Graph::BFS_show(std::string _StartingEdge) const
	{
		Point* s0 = (m_points.find(_StartingEdge))->second;
		std::unordered_map<std::string, std::string> l_pred;
		std::cout << "BFS_course a partir de " << _StartingEdge << " :" << std::endl;
		l_pred = s0->BFS_course();
		for (auto s : l_pred) {
			std::cout << s.first << " <--- ";
			std::pair<std::string, std::string> pred = s;
			while (pred.second != _StartingEdge) {
				pred = *l_pred.find(pred.second);
				std::cout << pred.first << " <--- ";
			}
			std::cout << _StartingEdge << std::endl;
		}
	}

	void Graph::DFS_show(std::string _StartingEdge) const
	{
		Point* s0 = (m_points.find(_StartingEdge))->second;
		std::unordered_map<std::string, std::string> l_pred;
		std::cout << "DFS_course a partir de " << _StartingEdge << " :" << std::endl;
		l_pred = s0->DFS_course();
		for (auto s : l_pred) {
			std::cout << s.first << " <--- ";
			std::pair<std::string, std::string> pred = s;
			while (pred.second != _StartingEdge) {
				pred = *l_pred.find(pred.second);
				std::cout << pred.first << " <--- ";
			}
			std::cout << _StartingEdge << std::endl;
		}
	}

	void Graph::BFS_course(std::string _StartingEdge) const
	{
		Point* s0 = (m_points.find(_StartingEdge))->second;
		std::unordered_map<std::string, std::string> l_pred;
		l_pred = s0->BFS_course();
	}

	void Graph::DFS_course(std::string _StartingEdge) const
	{
		Point* s0 = (m_points.find(_StartingEdge))->second;
		std::unordered_map<std::string, std::string> l_pred;
		l_pred = s0->DFS_course();
	}*/

	//std::unordered_map<Point*, std::list<Point*>> Graph::smaller_travel(const Point& _DepartPoint, bool reverse = false) const
		/**
		This function do the Djisktra's algorithm in smallest or biggest travel distance, return an unordered map with The depart point and the list of all points to travel through
		**/
	//{
		//Declaration d'une unordered map avec id et unsigned int (valeur des ar�tes)
	//}

	/*Graph Graph::Prim_algorithm(const Point& _DepartPoint) const
	{
		//return Graph();
	}



	int Graph::research_show_CC() const
	{
		int i = 0;
		std::unordered_set<std::string> comp_co;
		std::cout << std::endl;
		for (const auto& it : m_points)                                    //pointeur auto qui va prendre tous les Points
		{

			if (comp_co.count(it.second->get_id()) == 0)               //condition de verification pour voir si le Point est dans la liste
			{
				++i;
				std::cout << "cc" << i << ":" << std::endl;
				it.second->researchCC(comp_co);                       //va rechercher les composantes connexes du Point s�lectionner
				std::cout << std::endl;

			}
		}
		return i;
	}
	*/
	void Graph::show_svg(Svgfile& _out)
	{
		/**
		Affiche le svg du graphe, update necessaire: ajouter un moyen de donner le point de r�f�rence depuis lequel tracer le graphe / Donner les co�ts des arr�tes
		**/
		for (const auto& it : m_points)
		{
			_out.addCircle(it.second->get_coord().get_x(), it.second->get_coord().get_y(), 6);
		}
		for (const auto& at : m_links)
		{
			_out.addLine((m_points.find(at.second->get_id_a()))->second->get_coord().get_x(), (m_points.find(at.second->get_id_a()))->second->get_coord().get_y(), (m_points.find(at.second->get_id_b()))->second->get_coord().get_x(), (m_points.find(at.second->get_id_b()))->second->get_coord().get_y());
		}
	}

	Graph::~Graph()
	{
	}




	//------------------POINT------------------
	Point::Point(std::string _Name, short _x, short _y) :m_id{ _Name }, m_Coord {_x,_y}
	{
	}
	void Point::addNeighboor( Link* _link, std::string _id)
		/**
		Ajout de voisin dans la liste
		**/
	{
		m_neighboors.insert({ _link,_id });
	}



	/*					PARTIE A REMETTRE SANS BUG

	std::unordered_map<std::string, std::string> Point::BFS_course() const
	{
		std::unordered_map<std::string, std::string> l_pred;
		std::queue<const Point*> file;
		file.push(this);//on ajoute l'element actuel dans la file
		const Point* s;
		std::vector<Point*> list_point; /// A changer si mieux
		do {
			s = file.front();//on recupere le Point de tete
			file.pop();
			for (size_t i = 0; i < s->m_neighboors.size(); i++)
			{
				if (l_pred.find(s->m_neighboors[i].first->m_id) == (l_pred.end()) && (s->m_neighboors[i]->first != this))
				{
					file.push(s->m_neighboors[i]->first);
					l_pred.insert({ s->m_neighboors[i]->first->m_id,s->m_id });
				}
			}

		} while (!file.empty());//on entre dans la boucle tant que la file n'est pas vide

		return l_pred;
	}

	std::unordered_map<std::string, std::string> Point::DFS_course() const
	{
		std::unordered_map<std::string, std::string> l_pred;
		std::stack<const Point*> pile;
		const Point* s;
		pile.push(this);
		while (!pile.empty())
		{
			s = pile.top();//on recupere le Point de tete
			pile.pop();
			for (size_t i = 0; i < s->m_neighboors.size(); i++)
			{
				if (l_pred.find(s->m_neighboors[i].first->m_id) == (l_pred.end()) && (s->m_neighboors[i]->first != this))
				{
					pile.push(s->m_neighboors[i]->first);
					l_pred.insert({ s->m_neighboors[i]->first->m_id,s->m_id });
				}
			}
		}


		return l_pred;
	}

	void Point::researchCC(std::unordered_set<std::string> & _cc) const
	{
		_cc.insert(m_id);
		std::cout << m_id << "   ";
		for (const auto& it : m_neighboors)
		{
			if (_cc.count(it.first->m_id) == 0)
				std::cout << it.second.get_weight();
			it.first->researchCC(_cc);/// on recherche tous les voisins par reconnaissance de parit�
		}
	}

	void Point::research_ps(int& _parity) const
	{
		if (m_neighboors.size() % 2 != 0)
			_parity = 1;
	}*/

	Point::~Point()
	{
	}


	//------------------LINK------------------
	Link::Link(std::string _id, float _cost1, float _cost2, std::string _a, std::string _b) : m_id{ _id }, m_cost1{ _cost1 }, m_cost2{ _cost2 }, m_point_A{ _a }, m_point_B{ _b }, m_mode{ 'n' }, m_coord_text{0,0}
	{
		std::cout << "Link constructor id:" << m_id + " " << m_cost1 << " " << m_cost2 << " " + m_point_A + " " + m_point_B << std::endl;
		//Calcul de l'emplacement exact d'�criture grace au mode et au coord du milieu
	}
//    Link::Link(Link& _link_cop)
//    {
//        m_cost1=_link_cop.m_cost1;
//        m_cost2= _link_cop.m_cost2;
//        m_mode=_link_cop.m_mode;  //mode of the link : horizontal: 'h' / vertical : 'v' / diagonal up right : 'r' / diagonal up left : 'l' and 'n' as null
//        m_coord_text=_link_cop.m_coord_text;  //Coord for the text (weights)
//
//        m_id=_link_cop.m_id;
//        m_point_A=_link_cop.m_point_A;
//        m_point_B=_link_cop.m_point_B;
//    }
//    Link::Link()
//    {
//
//    }




///Rajout d�gueulasse pour bypass un bug
// Btw quand tu s�pareras les fichier include le main .h ici je pense que le bug vient de la mais je dois dodo je test en me levant
// pense a rajouter dans le main vector.h



// pense a rajouter dans le main vector



Path::Path()
{
    /// a j'ai oubli� de mettre l'init des cout totaux et je me parle a moi m�me en texte c'est rigolo
}

Path::~Path()
{

}

void  Path::add_link(Link* lien)
{
    trace.push_back (lien);


}

/// J'ai tout chang� pour passer en bool�en donc loin d'etre fini
/// la j'aimerai faire un systeme qui me prend le nombre d'arrete en bool�en. A achaque tour ++ sur le bool�en puis tu fais un if ( somme de tous les bool�ens == graphe.getsizempoint ) et pour chaque cas
/// tu vas l'enregistrer dans un vect a part puis pour chaque truc de ce nouveau vect faut traduire le bool�en en id de vecteur. nos vecteur ont une id 1 puis 2 etc donc tu dis le bool�en tout a droite c'est le vect 1 etc
/// et la on test chacun des cas pour voir si ils sont convexe et on les vire du vec si c'est le cas
/// deuxieme verif tous les point pr�sents *
/// non convex
/// puis on balance le vec dans l'algo en bas et c'est bon
/// et oui y'a pas mass code j'ai pris longtemps a bien biter ce que je devais faire je galerer a trouver un truc qui fasse pas tourner le programme en 50 ans puis j'ai relu la consigne ...
/// Btw �a va aussi me permettre d'optimiser pareto au besoin
//void get_all_path(Graph graph,std::vector<Path*> chemin_possible)// �tudie tous les cas possible
//{
//        std::vector<bool> liste_vec;
//        int i ;
//        for (i=0;i=pow(2,graph.get_size_m_link());i++)
//                {
//                    liste_vec->clear();
//                    liste_vec->resize(bool,graph.get_size_m_link());
//
//
//
//
//                }
//
//
//
//
//}




/// ce qui a dessous est fonctionnel mais non opti
/// Solution opti a refaire :trier par ordre d�croissant d'un des couts avant comme �a moins de boucle
/// en fonction des deux couts
/// et on fait passer la v�rif dans l'une ou l'autre des boucle en fonction de quel cout et le plus �lev� dans le chemin actuel

// est cens� marcher
  void pareto_verif( std::vector <Path*> chemin_possible ) // Algo qui efface tous les chemins qui ne sont pas pareto optimo
{
    unsigned int  i,y;
    for(i=0;i<chemin_possible.size();i++)
    {
        for(y=0;y<chemin_possible.size();y++)
        {
            if(y!=i)
           {
               if(chemin_possible[i]->get_tot1()<chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<=chemin_possible[y]->get_tot2())
                   chemin_possible.erase(chemin_possible.begin()+i);
               else if (chemin_possible[i]->get_tot1()<=chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<chemin_possible[y]->get_tot2())
                          chemin_possible.erase(chemin_possible.begin()+i);
           }
        }

    }
}









