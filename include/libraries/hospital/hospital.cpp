#include "hospital.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>
#include <utility>

// Declaraciones de ID class.

Hospital::ID::ID()
    : id_(new char[12]) {} // Crar un arreglo dinamico de 12 caracteres, vacio.
Hospital::ID::ID(char const *id) : id_(new char[12]) {
  // Comprobamos que el char const *id contenga 11 caracteres.

  if (isInvalid(id))
    throw std::invalid_argument(ID_ERROR);

  // copiamos el id hacia id_
  std::strcpy(id_.get(), id);
}

Hospital::ID::~ID() {}

bool Hospital::ID::operator==(char const *id) {
  // Sobrecarga del operador de igualdad para hacer comprobaciones
  if (std::strlen(id_.get()) == std::strlen(id))
    for (std::size_t i{0}; i < size; i++)
      if (id_[i] != id[i])
        return false;

  return true;
}
bool Hospital::ID::operator==(ID const &id) {
  if (std::strlen(id_.get()) == std::strlen(id.id_.get()))
    for (std::size_t i{0}; i < size; i++)
      if (id_[i] != id.id_[i])
        return false;

  return true;
}
char Hospital::ID::operator[](std::size_t index) {
  // Sobrecarga del operador [], para acceder a un elemento por su indice.
  return id_[index];
}
char const *Hospital::ID::c_str() { return id_.get(); }

//-------------------------------------------------------------------------------------
// Declaraciones de Paciente class.

std::map<std::string, int> Hospital::Paciente::CONTADOR{};
int Hospital::Paciente::MAX{0};
long int Hospital::Paciente::TOTAL_AGE{0};
long int Hospital::Paciente::TOTAL_PACIENTES{0};

Hospital::Paciente::Paciente(h_parameters &&parameters)
    : name_(std::get<0>(parameters)), last_name_(std::get<1>(parameters)),
      municipalitie_(std::get<2>(parameters)),
      num_sala_(std::get<3>(parameters)), num_bed_(std::get<4>(parameters)),
      age(std::get<5>(parameters)), sex(std::get<6>(parameters)),
      id_(std::get<7>(parameters)) {

  if (num_sala_ < NUM_MIN_SALA_AND_BED || num_sala_ > NUM_MAX_SALA)
    throw std::invalid_argument(SALA_ERROR);

  if (num_bed_ < NUM_MIN_SALA_AND_BED || num_bed_ > NUM_MAX_BED)
    throw std::invalid_argument(BED_ERROR);

  TOTAL_AGE += age;
  TOTAL_PACIENTES++;
  CONTADOR[municipalitie_]++;

  if (CONTADOR[municipalitie_] > MAX)
    MAX = CONTADOR[municipalitie_];
}

Hospital::Paciente::~Paciente() {}

std::string
Hospital::Paciente::itsRegister(h_parameters const *parameter) noexcept {
  char const *id{std::get<7>(*parameter)};
  if (num_sala_ == std::get<3>(*parameter) &&
      num_bed_ == std::get<4>(*parameter))
    return SAME_SALA_BED;

  if (id_ == id)
    return SAME_ID;

  return "";
}

//-------------------------------------------------------------------------------------
// Declaraciones de Hospital class.

Hospital::~Hospital() {}

Hospital::Paciente *Hospital::orderLists(std::size_t num_sala,
                                         Paciente &&paciente) {
  // Funcion para ordenar igrsar un nuevo paciente a la lista pero manteniedo
  // esta ordenada.

  // Con lower_bound buscamos cual es la direccion en memoria donde debemos
  // ingresar nuestro objeto.
  auto it = std::lower_bound(
      salas_[num_sala].begin(), salas_[num_sala].end(), paciente,
      [](Paciente const &p1, Paciente const &p2) -> bool {
        return p1.name_ < p2.name_;
      });

  // Tomar la posicion en memoria que ocupa el nuevo paciente ingresado a la
  // lista
  auto pos = salas_[num_sala].insert(it, std::move(paciente));

  return &(*pos); // Direccion de memoria de dicho pasciente ingrsado
}

void Hospital::setPaciente(h_parameters &&data) {
  // Funcion para ingrsar nuevos pacientes a las listas de las salas del
  // hospital.

  for (auto &sala : salas_) {
    for (auto &paciente : sala.second) {
      auto message = paciente.itsRegister(&data);
      if (!message.empty())
        throw std::invalid_argument(message);
    }
  }

  std::size_t num_sala = std::get<3>(data); // <3> Numero de sala

  // Comprobamos si este  paciente esta ingresado en esta sala.
  auto if_in = salas_.find(num_sala);

  auto cant_por_sexo = [this](Sex sexo) {
    // Permite contar la cant de personas por sexo que se han ingresado
    switch (sexo) {
    case Sex::M:
      total_M += 1;
      return;
    case Sex::F:
      total_F += 1;
      return;
    default:
      return;
    }
  };

  Hospital::Paciente *pos;

  if (!salas_.empty() && if_in != salas_.end()) {
    // En caso de estar vacio el mapa y de haber pacientes en la sala.
    try {
      // Comprobamos que no se levanta una excepcion

      pos = orderLists(
          num_sala,
          Paciente(std::move(data))); // posicion del paciente ingresado
    } catch (std::invalid_argument const &exc) {
      // Capturamos la exception y la volvemos a levantar, impidiendo que se
      // ingrese el paciente
      throw exc;
    }

    cant_por_sexo(pos->sex);
  } else {
    // En caso de estar vacio el map o de no haber pacientes en esta sala.
    list_pacientes new_pacientes_list{Paciente(
        std::move(data))}; // creamos la lista para estos nuevos pacientes

    salas_.insert({num_sala, new_pacientes_list}); // insertamos el paciente
                                                   // actual a la lista creada
    try {
      // Comprobamos que no se levanta una excepcion

      list_pacientes new_pacientes_list{Paciente(
          std::move(data))}; // creamos la lista para estos nuevos pacientes

      salas_.insert({num_sala, new_pacientes_list}); // insertamos el paciente
                                                     // actual a la lista creada
    } catch (std::invalid_argument const &exc) {
      // Capturamos la exception y la volvemos a levantar, impidiendo que se
      // ingrese el paciente

      throw exc;
    }

    pos = &salas_[num_sala].front(); // posicion del objeto ingresado

    cant_por_sexo(pos->sex);
  }
}

void Hospital::encimaMedia() noexcept {
  // Controlamos quienes son los pacientes con edad superior a la media.

  edad_media =
      static_cast<double>(Paciente::TOTAL_AGE) / Paciente::TOTAL_PACIENTES;

  for (auto &pair : salas_)
    for (auto &p : pair.second)
      if (p.age > edad_media)
        pasientes_edad_encima_media.push_back(&p);
}
bool Hospital::estaIngresado(char const *id) noexcept {
  // Conprobamos si el paciente se encuentra ingrsado en el hospital.

  for (auto &pacientes : salas_)
    for (auto &paciente : pacientes.second)
      return paciente.id_ == id; // retorna true en caso de estar en la sala

  return false;
}

std::size_t Hospital::cantMan() const noexcept { return total_M; }
std::size_t Hospital::cantWoman() const noexcept { return total_F; }
Hospital::max_municipalities Hospital::maxMunicipalitie() noexcept {
  // Contromas cual(es)  es(son) el(los) municipio(s) con la maxima cant de
  // pacientes.

  for (auto &mname_rep : Paciente::CONTADOR)
    if (mname_rep.second == Paciente::MAX)
      max_place.push_back(&mname_rep.first);

  return max_place;
}
Hospital::list_ref_pacientes Hospital::getEdadEncimaMedia() noexcept {
  encimaMedia();
  return pasientes_edad_encima_media;
}

Hospital::list_pacientes Hospital::aSala(std::size_t num_sala) noexcept {
  return salas_[num_sala];
}

Hospital::Paciente *Hospital::idAt(char const *id) {
  if (Hospital::ID::isInvalid(id) || !estaIngresado(id))
    throw std::invalid_argument(ID_ERROR_NOT_HERE);

  for (auto &pacientes : salas_)
    for (auto &paciente : pacientes.second)
      if (paciente.id_ == id)
        return &paciente;

  return nullptr;
}

std::list<Hospital::Paciente> &Hospital::operator[](std::size_t index) {
  if (index < Paciente::NUM_MIN_SALA_AND_BED || index > Paciente::NUM_MAX_SALA)
    throw std::invalid_argument(SALA_ERROR);
  return salas_[index];
}
