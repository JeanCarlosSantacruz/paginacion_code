#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Pagina {
  int idProceso; // ID del proceso al que pertenece la página (-1 si está vacía)
};

struct Proceso {
  int id;
  int sizeProceso;
  std::vector<int> paginasAsignadas; // Lista de páginas asignadas al proceso
};

class SimuladorPaginacion {
private:
  int tamMemoria;
  int tamPagina;
  std::vector<Pagina> memoriaPaginada;
  std::vector<Proceso> procesos;

public:
  SimuladorPaginacion(int size, int tamPagina)
      : tamMemoria(size), tamPagina(tamPagina) {
    int numPaginas = tamMemoria / tamPagina;
    memoriaPaginada.resize(numPaginas, {-1});
  }

  // AsignarMemoria a paginas
  bool asignarMemoria(Proceso &proceso) {
    int numPaginasNecesarias = (proceso.sizeProceso + tamPagina - 1) /
                               tamPagina; // Redondeo hacia arriba
    int paginasAsignadas = 0;

    for (int i = 0; i < memoriaPaginada.size(); ++i) {
      if (memoriaPaginada[i].idProceso == -1) {
        int paginasDisponibles = 1;

        // Contar las páginas consecutivas disponibles
        for (int j = i + 1; j < memoriaPaginada.size(); ++j) {
          if (memoriaPaginada[j].idProceso == -1) {
            paginasDisponibles++;
          } else {
            break; // Detenerse si encuentra una página ocupada
          }
        }

        // Asignar páginas si hay suficientes
        if (paginasDisponibles >= numPaginasNecesarias) {
          for (int j = i; j < i + numPaginasNecesarias; ++j) {
            memoriaPaginada[j].idProceso = proceso.id;
            proceso.paginasAsignadas.push_back(j);
            paginasAsignadas++;
          }

          std::cout << "Proceso " << proceso.id << " asignado a páginas ";
          for (int pagina : proceso.paginasAsignadas) {
            std::cout << pagina << " ";
          }
          std::cout << std::endl;
          return true;
        }
      }
    }

    std::cout << "No hay suficiente espacio para asignar el proceso "
              << proceso.id << std::endl;
    return false;
  }

  // Liberar Memoria
  void liberarMemoria(Proceso &proceso) {
    for (int pagina : proceso.paginasAsignadas) {
      memoriaPaginada[pagina].idProceso = -1;
    }

    proceso.paginasAsignadas.clear();
    std::cout << "Memoria del proceso " << proceso.id << " liberada."
              << std::endl;
  }

  // Función para imprimir el estado de la memoria paginada
  void imprimirEstadoMemoria() const {
    std::cout << "Estado de la memoria paginada:" << std::endl;
    for (int i = 0; i < memoriaPaginada.size(); ++i) {
      std::cout << "Página " << i << ": ";
      if (memoriaPaginada[i].idProceso == -1) {
        std::cout << "Libre";
      } else {
        std::cout << "Proceso " << memoriaPaginada[i].idProceso;
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

int main() {
  int tamMemoria = 100;
  int tamPagina = 20;
  SimuladorPaginacion simulador(tamMemoria, tamPagina);

  // Procesos de prueba
  Proceso proceso1 = {1, 30, {}};
  Proceso proceso2 = {2, 15, {}};
  Proceso proceso3 = {3, 50, {}};
  Proceso proceso4 = {4, 100, {}};
  Proceso proceso5 = {5, 25, {}};
  Proceso proceso6 = {6, 40, {}};

  // Imprimir estado de la memoria
  simulador.imprimirEstadoMemoria();

  // asignaciones
  simulador.asignarMemoria(proceso1);
  simulador.asignarMemoria(proceso2);
  simulador.asignarMemoria(proceso3);
  simulador.asignarMemoria(proceso4);
  simulador.asignarMemoria(proceso5);
  simulador.asignarMemoria(proceso6);

  // Imprimir estado de la memoria
  simulador.imprimirEstadoMemoria();

  // Liberar memoria de un proceso
  simulador.liberarMemoria(proceso1);

  // Imprimir estado de la memoria después de liberar
  simulador.imprimirEstadoMemoria();

  return 0;
}
