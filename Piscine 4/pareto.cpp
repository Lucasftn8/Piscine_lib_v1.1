#include  "main.h"


void get_path(Graph &graph,std::vector<Path*> &chemin_possible)
{
  unsigned  int i,j,y,z=0,nblien,verif1,verif2,nbtour=0,nb2tour=0,nbtour3=0,valueon, intermediaire;

    Path try_it;
   // std::vector<int> keep_trying;
    std::vector<unsigned int> selection_point;
    std::vector<unsigned int> reset_selec_point;
    for(i=0;i<graph.get_m_points().size();i++)
        selection_point.push_back(0);
    for(i=0;i<graph.get_m_points().size();i++)
        reset_selec_point.push_back(0);
    for(i=0;i<pow(2,graph.get_m_link().size());i++)
    {
               std::string chaine = (std::bitset<36>(i).to_string()).substr((char)36 - (char)graph.get_m_link().size(), 35);// pour chaque cas
               nblien=0;
             //  std::cout<< "nbcas" <<chaine.size()<<std::endl;


            nbtour++;
            for (j=0;j<chaine.size();j++)
            {
               if(chaine[j]=='1')
                nblien++;


              //  std::cout<< nbtour                << std::endl;
            }
                if (nblien==(graph.get_m_points().size()-1)) /// si le chemin a arrete == ordre n-1
            {
              //  std::cout<<"nblienpassant"<<graph.get_m_points().size()-1<<std::endl;
              //   nb2tour++;
                  //  std::cout<<"nblien"<<nblien<<std::endl;
                   // std::cout <<"  graph get m point size apr�s nb lien " << graph.get_m_points().size() <<std::endl;
                    try_it.reset();
                    for (j=0;j<chaine.size();j++)/// Creer le path en arrette et non en bool�en
                    {
                     //   std::cout<< " verifchaine" <<chaine.size()<<std::endl;
                        if(chaine[j]=='1')
                        {
                     //           std::cout<< "bug "<< std::endl;
                                    try_it.add_link(graph.get_m_link()[j]);
                                 //   std::cout <<"try it " <<std::endl;
//                                    try_it.afficher_path();


                        }

                    }
                    // chemin_possible.push_back(new Path(try_it));

                       // std::cout<<"taille "<<try_it.get_trace_size()<<std::endl;
    //                    / Verif que tous les sommets sont pr�sent dans le chemin try it a termin�
    //                    / il faut en meme temps s'assurer qu'il n'y ait pas de boucle ce qui veut dire qu'il ne faut pas que les 2 id d'un lien soit d�ja pr�sent dans le vecteur keep trying
    //                    /pas manger depuis ce matin 4h donc je prend une pause
    //                    / apr�s avoir fait la v�rif si tout est bon on ajoute le chemin a chemin_possible avec un pushback et est fini :!!!
                    //    keep_trying.clear();
                        verif1=0;
                        verif2=0;
                        ///test connexe a refaire
                           ///test connexe a refaire
                        /// La mon Ptitlu il faudrais qu'on fasse le tableau de connexit� pour s'assurer que le graphe est connexe
                        /// vu que chez moi ici �a compile pas je te l'�crit en francais
                        /// pour chque lien //
                        ///le point a et le point b  du lien selectionne on regarde lequel est le plus bas ici a pour l'exemple
                        ///alors la mark de b et tous les points dont la mark = la mark de b prennent la mark de a .
                        /// si tous les points on la m�me marque le graph est enti�rement connecter.
                        /// ce qui suit est LA CONDITION A AVOIR
                        /// il est cependant interdit d'avoir un lien dont le point A et B ont la m�me ID
                        /// si les conditoin sont valid� il faut activ� la ligne 53
                        /// bisous

                        /// Ps je t'ai fait des zolies get et set pour te donner du courage

                       // std::cout <<"  graph get m point size avant test connex" << graph.get_m_points().size() <<std::endl;
                         for (y=0;y<try_it.get_trace_size();y++)
                         {
                              //std::cout << "michel ici tout va bien " << std::endl;
                             if (graph.get_m_points()[try_it.get_trace()[y]->get_id_a()]->get_marked()<graph.get_m_points()[try_it.get_trace()[y]->get_id_b()]->get_marked()) // si la marque de a est inferieur a la marque de b
                             {
                                 // std::cout << "pablo ici tout va bien " << std::endl;
                                 intermediaire=graph.get_m_points()[try_it.get_trace()[y]->get_id_b()]->get_marked();// inter = mark b
                                  //std::cout << "le frere de pablo ici tout va bien " << std::endl;
                                  //std::cout <<"  graph get m point size" << graph.get_m_points().size() <<std::endl;
                                 // std::cut << "z  frere qu'est ce que t'as? " << z <<std::endl;
                                 for(z=0;z<graph.get_m_points().size();z++)// pour tous les points de get_m point
                                 {
                                   //   std::cout << "ferdinant ici tout va bien " << std::endl;
                                     if (intermediaire==graph.get_m_points()[z]->get_marked())    // si leur mark = a la mark d'intermediaire et donc de b
                                     graph.get_m_points()[z]->set_marked(graph.get_m_points()[try_it.get_trace()[y]->get_id_a()]->get_marked());// elles prennent la valeur de la mark de a
                                 }
                             }
                             else if (graph.get_m_points()[try_it.get_trace()[y]->get_id_a()]->get_marked()>graph.get_m_points()[try_it.get_trace()[y]->get_id_b()]->get_marked())
                             {
                                 intermediaire=graph.get_m_points()[try_it.get_trace()[y]->get_id_a()]->get_marked();
                               //    std::cout << "z2  frere qu'est ce que t'as? " << z <<std::endl;
                                 for(z=0;z<graph.get_m_points().size();z++)
                                 {
                                //     std::cout << "ferdinant2 ici tout va bien " << std::endl;
                                     if (intermediaire==graph.get_m_points()[z]->get_marked())
                                     graph.get_m_points()[z]->set_marked(graph.get_m_points()[try_it.get_trace()[y]->get_id_b()]->get_marked());
                                 }
                             }
                         }
                       //  std::cout << "roger ici tout va bien " << std::endl;
                        // std::cout <<"  graph get m point size" << graph.get_m_points().size() <<std::endl;
                         for(z=0;z<graph.get_m_points().size()&&verif2!=1;z++)
                         {
                            // std::cout << "bernard ici tout va bien " <<std::endl;
                             if (verif1!=graph.get_m_points()[z]->get_marked())
                             {
                                verif2=1;
                              //  std::cout <<"verif 2 =1 ici" <<std::endl;
                             }
                              //  std::cout <<"  graph get m point size" << graph.get_m_points().size() <<std::endl;
                         }
                         if (verif2==0)
                         {
                            chemin_possible.push_back(new Path(try_it));
                           // std::cout << "Iri ici tout va bien " <<std::endl;
                         }

                         for(z=0;z<graph.get_m_points().size();z++)
                         {
                             graph.get_m_points()[z]->reset_mark();
                         }









//                        for (y=0;y<try_it.get_trace_size();y++) /// test si il est connexe
//                        {
//                            for (z=0;z<graph.get_m_points().size();z++)
//                            {
//                                    if(try_it.get_trace()[y]->get_id_a()==graph.get_m_points()[z]->get_id())
//                                 {
//                                     if(selection_point[z]==0)
//                                        selection_point[z]=1;
//                                     else
//                                        verif1=1;
//                                 }
//                                 if(try_it.get_trace()[y]->get_id_b()==graph.get_m_points()[z]->get_id())
//                                 {
//                                 if(selection_point[z]==0)
//                                    selection_point[z]=1;
//                                 else
//                                    verif2=1;
//                             }
//
//                        }
                    }
//                     if (verif1!=1||verif2!=1)
//                             {
///** Tu ajoutes try it la valeur de try it qui est une variable d�clar� dans la fonction mais qui disparais apr�s alors ton chemin pointe juste sur une adresse m�moire**/
//                                 chemin_possible.push_back(new Path(try_it));  /// si il ne l'est pas l'ajoute aux chemin possible pour pareto
//                                 //chemin_possible.push_back(&try_it);  /// si il ne l'est pas l'ajoute aux chemin possible pour pareto
//
//                             }
            }
//               	for(i=0;i<chemin_possible.size();i++)
//    {
//                    //     std::cout <<" Chemin qui devrait etre bon "<<i<<std::endl;
//                     //    chemin_possible[i]->afficher_path();
//
//
//    }
std::cout <<    " nb chemin a red�finir " <<chemin_possible.size() <<std::endl;
std::cout <<"nbtour" <<nbtour <<std::endl;
    }
   // std::cout<< "test1 ok "<< nbtour<<std::endl;
    // std::cout<< "testzrafvg ok "<< nb2tour<<std::endl;
//     std::cout<<"ajout_try_it"<<nbtour3<<std::endl;
  //  std::cout<<" nombre d'input a la verif d'apr�s"<<chemin_possible.size()<<std::endl;
   // std::cout<<"tot 1 ici" << chemin_possible[0]->get_tot1()<<std::endl; /// ici est toujours bon
//}

  void pareto_verif( std::vector <Path*> &chemin_possible, std::vector<Path*> &chemin_pareto ) // Algo qui efface tous les chemins qui ne sont pas pareto optimo
{

    unsigned int  i,y,nbtour=0,nbtour2=0,verif=0;
  //  std::cout<<chemin_possible.size()<<std::endl;
    for(i=0;i<chemin_possible.size();i++)
        {
            verif=0;
             if (chemin_possible[i]->get_tot1()==45&&chemin_possible[i]->get_tot2()==30)
                std::cout <<" WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"<< std::endl;
            if (chemin_possible[i]->get_tot1()==48&&chemin_possible[i]->get_tot2()==27)
                std::cout <<" WTFFFFFFFFFFFFF5FFFFFFFFFFFFFFFFFFFFFFFFFF2"<< std::endl;
        for(y=0;y<chemin_possible.size()&&verif!=1;y++)
        {

            if(y!=i)
           {
              //   std::cout<<"cout 1        "<<chemin_possible[i]->get_tot1()<< "et   "<<chemin_possible[y]->get_tot1()<<"       "  ;
                // std::cout<<"cout 2        "<<chemin_possible[i]->get_tot2()<< "et   "<<chemin_possible[y]->get_tot2()<<std::endl;
//






                 if(chemin_possible[i]->get_tot1()>chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()>= chemin_possible[y]->get_tot2())
                 {
                          verif=1;
                 }
                 else if(chemin_possible[i]->get_tot1()>=chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()> chemin_possible[y]->get_tot2())
                 {
                          verif=1;
                 }
//                 else if (chemin_possible[i]->get_tot1()==chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<chemin_possible[y]->get_tot2())
//                 {
//                          verif++;
//                 }
//                 else if (chemin_possible[i]->get_tot1()<chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<chemin_possible[y]->get_tot2())
//                 {
//                          verif++;
//                 }
//               if(chemin_possible[i]->get_tot1()<chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<=chemin_possible[y]->get_tot2())
//               {
//                          chemin_possible.erase(chemin_possible.begin()+i);
//               }
//               else if (chemin_possible[i]->get_tot1()<=chemin_possible[y]->get_tot1()&&chemin_possible[i]->get_tot2()<chemin_possible[y]->get_tot2())
//               {
//                          chemin_possible.erase(chemin_possible.begin()+i);
//               }
           }
        }
       // std::cout <<std::endl<<" verif " <<verif <<std::endl;
        if(verif==0)
        {
            chemin_pareto.push_back(chemin_possible[i]);
          //  chemin_possible[i]->afficher_path();
        }

    }
  //  std::cout<<"nb de truc efface  " <<nbtour<<std::endl;
  std::cout<< "taille de chemin pareto  "<<chemin_pareto.size()<<std::endl;
   // std::cout<< "nombre de truc pouvant etre efface"<<nbtour2<<std::endl;
}



//  void pareto_verif( vector< Path* > chemin_possible ) // Algo qui efface tous les chemins qui ne sont pas pareto optimo
//{
//    int i,y;
//    for(i=0;i<chemin_possible.size;i++)
//    {
//        for(y=0;y<chemin_possible;y++)
//        {
//            if(y!=i)
//           {
//
//               if(chemin_possible[i]->cout_tot1<chemin_possible[y]->cout_tot1&&chemin_possible[i]->cout_tot2<=chemin_possible[y]->cout_tot2)
//                    chemin_possible[i].erase;
//               else if (chemin_possible[i]->cout_tot1<=chemin_possible[y]->cout_tot1&&chemin_possible[i]->cout_tot2<chemin_possible[y]->cout_tot2)
//                          chemin_possible[i].erase;
//           }
//        }
//
//    }
//}



