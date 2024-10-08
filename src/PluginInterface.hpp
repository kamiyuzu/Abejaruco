#include <string>
#include <tuple>
#include <variant>
#include <vector>

//Posibles tipos para todos los parametros configurables en un plugin
//Es como una union, solo que puedes comprobar con seguridad el tipo
//que hay por debajo en tiempo de ejecucion
//Se pueden añadir o quitar tipos segun se necesiten
typedef std::variant<
    unsigned int,
    double,
    const std::vector<double>
> ParamType;

//Interfaz basica que debe implementar cada plugin
class PluginInterface {
    public:
        virtual ~PluginInterface() = default;
        virtual std::vector<double> execute() = 0;
        //Vector con todos los parametros ajustables
        virtual const std::vector<std::string> getParameters() = 0;
        //Cambia el valor de un parametro
        //Devuelve error por valor estilo C, se podria usar excepciones
        virtual int setParameter(const std::tuple<std::string, ParamType>& value) = 0;
};

//En la implementacion, lo unico que debe de hacer es
//devolver el resultado de llamar al constructor de la clase que sea
//Es necesario para que al cargar el .so se pueda encontrar el simbolo
//de esta funcion para llamarla, ya que a los simbolos de las funciones
//nativas de C++ se les aplica name mangling
extern "C" PluginInterface* createPlugin();
