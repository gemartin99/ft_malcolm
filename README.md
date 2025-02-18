# 🕵️‍♂️ ft_malcolm 

## 📜 Descripción
**ft_malcolm** es un proyecto de la escuela 42 que consiste en manipular tráfico ARP para modificar las direcciones MAC asociadas a determinadas IPs dentro de una red local. Este tipo de ataque se conoce como ARP spoofing y permite interceptar tráfico entre dispositivos.

## 🖥️ Uso 
### Modo básico
```bash
./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

### Modo avanzado (con flags opcionales)
```bash
./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac> [FLAGS]
```

### 🏳️ Flags disponibles:
- `-h`, `--help` → Muestra la ayuda y el uso del programa.
- `-o`, `--output <archivo>` → Especifica un archivo de salida para logs (por defecto `output.log`).
- `-v`, `--verbose` → Muestra información detallada de cada paquete interceptado.
- `-s`, `--silent` → No muestra salida en terminal, solo escribe en el archivo de logs si está habilitado.

## 🛠️ Ejemplo de ejecución
```bash
./ft_malcolm 192.168.0.42 aa:bb:cc:dd:ee:ff 192.168.0.3 11:22:33:44:55:66 -v
```

## 📌 Requisitos
- Sistema operativo Linux 🐧
- Permisos de superusuario (`sudo`) 🔑
- Librería: `libpcap` 📚

## ⚒️ Instalación y compilación 
```bash
git clone https://github.com/gemartin99/ft_malcolm.git
cd ft_malcolm
make
```

## Notas importantes ⚠️
- Este programa es solo para **fines educativos** y debe ser usado en entornos controlados.
- La manipulación de tráfico de red sin autorización puede ser ilegal.

# Autor ✍🏼

<table>
  <tr>
    <td align="center"><a href="https://github.com/gemartin99/"><img src="https://avatars.githubusercontent.com/u/66915274?v=4" width="100px;" alt="100px"/><br /><sub><b>gemartin</b></sub></a><br /><a href="https://profile.intra.42.fr/users/gemartin" title="Intra 42"><img src="https://img.shields.io/badge/Barcelona-FFFFFF?style=plastic&logo=42&logoColor=000000" alt="Intra 42"/></a></td>
  </tr>
</table>

# Contacto 📥

◦ Email: gemartin@student.42barcelona.com

◦ Linkedin: https://www.linkedin.com/in/gemartin99/

# Quizás pueda interesarte!

### - Para ver mi progresion en el common core 42 ↙️

[AQUÍ](https://github.com/gemartin99/42cursus)

### - Mi perfil en la intranet de 42 ↙️
[AQUÍ](https://profile.intra.42.fr/users/gemartin)


