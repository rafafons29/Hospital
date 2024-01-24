#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <cstddef>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

enum class Sex { M = 'M', F = 'F' };
using h_parameters =
    std::tuple<std::string, std::string, std::string, std::size_t, std::size_t,
               std::size_t, Sex, const char *>;

class Hospital {

  struct ID {
    ID();
    ID(char const *);
    ~ID();
    bool operator==(char const *id);
    bool operator==(ID const &id);
    char operator[](std::size_t);
    char const *c_str();

    inline static bool isInvalid(const char *id) {
      return std::strlen(id) != 11;
    }

  private:
    std::shared_ptr<char[]> id_;
    std::size_t size{11};
  };

  struct Paciente {

    std::string name_;          //<0>
    std::string last_name_;     //<1>
    std::string municipalitie_; //<2>
    std::size_t num_sala_;      //<3>
    std::size_t num_bed_;       //<4>
    std::size_t age;            //<5>
    Sex sex;                    //<6>
    ID id_;                     //<7>

    static std::map<std::string, int> CONTADOR;
    static int MAX;
    static long int TOTAL_AGE;
    static long int TOTAL_PACIENTES;
    static constexpr std::size_t NUM_MIN_SALA_AND_BED{1};
    static constexpr std::size_t NUM_MAX_SALA{15};
    static constexpr std::size_t NUM_MAX_BED{50};

    Paciente() = default;
    Paciente(h_parameters &&); // Move constructor
    ~Paciente();

    std::string itsRegister(h_parameters const *parameter) noexcept;
  };

  using map_pacientes = std::map<std::size_t, std::list<Paciente>>;
  using hospital_iter = std::map<std::size_t, std::list<Paciente>>::iterator;
  using list_pacientes = std::list<Paciente>;
  using list_ref_pacientes = std::list<Paciente *>;
  using max_municipalities = std::vector<std::string const *>;

  map_pacientes salas_;
  list_ref_pacientes pasientes_edad_encima_media;
  max_municipalities max_place;
  std::size_t total_M{0};
  std::size_t total_F{0};
  float edad_media{0};
  int max_mun{0};

  Paciente *orderLists(std::size_t num_sala, Paciente &&paciente);
  void encimaMedia() noexcept;

public:
  Hospital() = default;
  ~Hospital();

  void setPaciente(h_parameters &&paciente);
  bool estaIngresado(char const *id) noexcept;
  std::size_t cantMan() const noexcept;
  std::size_t cantWoman() const noexcept;
  max_municipalities maxMunicipalitie() noexcept;
  list_ref_pacientes getEdadEncimaMedia() noexcept;
  list_pacientes aSala(std::size_t num_sala) noexcept;
  Paciente *idAt(char const *);

  inline std::size_t size() { return salas_.size(); }
  inline hospital_iter begin() { return salas_.begin(); }
  inline hospital_iter end() { return salas_.end(); }

  std::list<Paciente> &operator[](std::size_t);

  static constexpr char const *SALA_ERROR{
      "El numero de sala debe de ser entre 1 y 15"};
  static constexpr char const *BED_ERROR{
      "El numero de la cama debe de ser entre 1 y 50"};
  static constexpr char const *ID_ERROR{"EL Id debe tener 11 caracteres"};
  static constexpr char const *ID_ERROR_NOT_HERE{
      "Ningun paciente tiene ese ID"};
  static constexpr char const *SAME_ID{"Este ID esta registrado"};
  static constexpr char const *SAME_SALA_BED{
      "En esta sala esa cama ya esta ocupada"};
};

#endif // HOSPITAL_HPP
