#include "Snap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;
//g++ -Wall -D__STDC_LIMIT_MACROS -O3 -DNDEBUG -o GraphExport GraphExport.cpp ../snap-core/Snap.o -I../snap-core -I../glib-core

// Print graph statistics
void PrintGStats(const char s[], PNEGraph Graph) {
  printf(" %s nodos %d, edges %d, esta vacia? = %s\n",
      s, Graph->GetNodes(), Graph->GetEdges(),
      Graph->Empty() ? "Si" : "No");
}

void GraphML(PNEGraph Graph) {
	//Variables
	ofstream file ("Wiki-Vote.graphml"); //Archivo de salida
	int i = 1;
	//GraphML:
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
		file << "<graph id=\"G\" edgedefault=\"directed\">\n";

		for (PNEGraph::TObj::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
			file << "<node id=\"" << NI.GetId() << "\"/>\n";
		}

		for (PNEGraph::TObj::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++, ++i){
			file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
		}

		file << "</graph>\n";
		file << "</graphml>\n";
		file.close();
	}
}

void GEXF(PNEGraph Graph) {
	//Variables
	ofstream file ("Wiki-Vote.gexf"); //Archivo de salida
	int i = 1;
	//GEXF:
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
		file << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
		file << "<nodes>\n";

		for (PNEGraph::TObj::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
			file << "<node id=\"" << NI.GetId() << "\" />\n";
		}

		file << "</nodes>\n";
		file << "<edges>\n";

		for (PNEGraph::TObj::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++, ++i){
			file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
		}

		file << "</edges>\n";
		file << "</graph>\n";
		file << "</gexf>\n";
		file.close();
	}
}

void GDF(PNEGraph Graph) {
	ofstream file ("Wiki-Vote.gdf"); //Archivo de salida
	//GDF:
	if (file.is_open()) {
		file << "nodedef>id VARCHAR\n";
		for (PNEGraph::TObj::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
			file << NI.GetId() << "\n";
		}

		file << "edgedef>source VARCHAR, destination VARCHAR\n";
		for (PNEGraph::TObj::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
			file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
		}

		file.close();
	}
}

void JSON(PNEGraph Graph) {
	ofstream file ("Wiki-Vote.json"); //Archivo de salida
	if (file.is_open()) {
		file << "{ \"graph\": {\n";
		file << "\"nodes\": [\n";
		for (PNEGraph::TObj::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); ){
			file << "{ \"id\": \"" << NI.GetId() << "\" }";
			if (NI++ == Graph->EndNI())
				file << " ],\n";
			else
				file << ",\n";
		}

		file << "\"edges\": [\n";
		for (PNEGraph::TObj::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); ){
			file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
			if (EI++ == Graph->EndEI())
				file << " ]\n";
			else
				file << ",\n";
		}
		file << "} }";

		file.close();
	}
}

int main(){
    //Variables de tiempo;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point finish;
    //Importar el grafo del text file a la Graph
    TSsParser Ss("Wiki-Vote.txt", ssfWhiteSep, true, true, true);
    PNEGraph Graph;
    Graph = TNEGraph::New();
    int SrcNId, DstNId, SrcColId = 0, DstColId = 1;

    start = high_resolution_clock::now();
    while (Ss.Next()) {
       if (! Ss.GetInt(SrcColId, SrcNId) || ! Ss.GetInt(DstColId, DstNId)) { continue; }
       if (! Graph->IsNode(SrcNId)) { Graph->AddNode(SrcNId); }
       if (! Graph->IsNode(DstNId)) { Graph->AddNode(DstNId); }
       Graph->AddEdge(SrcNId, DstNId);
      }
       Graph->Defrag();
    finish = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( finish - start ).count();

       PrintGStats("Datos de la grafica: ",Graph);  
       cout<<"Tiempo para importar el dataset a la grafica: "<<duration<<endl;

    //Exportacion de la grafica
    start = high_resolution_clock::now();
    GraphML(Graph);
    finish = high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( finish - start ).count();
    cout<<"Tiempo para exportar la grafica en formato GraphML: "<<duration<<endl;
    
    start = high_resolution_clock::now();
    GEXF(Graph);
    finish = high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( finish - start ).count();
    cout<<"Tiempo para exportar la grafica en formato GEXF: "<<duration<<endl;

    start = high_resolution_clock::now();
    GDF(Graph);
    finish = high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( finish - start ).count();
    cout<<"Tiempo para exportar la grafica en formato GDF: "<<duration<<endl;

    start = high_resolution_clock::now();
    JSON(Graph);
    finish = high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( finish - start ).count();
    cout<<"Tiempo para exportar la grafica en formato JSON: "<<duration<<endl;



    return 0;

}