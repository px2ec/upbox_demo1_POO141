-- phpMyAdmin SQL Dump
-- version 4.2.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 09, 2014 at 01:18 AM
-- Server version: 5.5.37-MariaDB-log
-- PHP Version: 5.5.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `ire`
--

-- --------------------------------------------------------

--
-- Table structure for table `2014-1_equipos`
--

CREATE TABLE IF NOT EXISTS `2014-1_equipos` (
`id` int(11) NOT NULL,
  `nombre` varchar(255) NOT NULL,
  `ciudad` int(4) NOT NULL DEFAULT '0',
  `acreditado` tinyint(1) NOT NULL DEFAULT '0',
  `participa_r1` tinyint(1) NOT NULL DEFAULT '0',
  `participa_r2` tinyint(1) NOT NULL DEFAULT '0',
  `ptje_ronda1` int(11) NOT NULL DEFAULT '0',
  `ptje_ronda2` int(11) NOT NULL DEFAULT '0',
  `ptje_progra` int(11) NOT NULL DEFAULT '0',
  `ptje_trabajo` int(11) NOT NULL DEFAULT '0',
  `ptje_rondas` int(11) NOT NULL DEFAULT '0',
  `ptje_total` int(11) NOT NULL DEFAULT '0',
  `turno_competir` int(11) NOT NULL DEFAULT '-1'
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=24 ;

--
-- Dumping data for table `2014-1_equipos`
--

INSERT INTO `2014-1_equipos` (`id`, `nombre`, `ciudad`, `acreditado`, `participa_r1`, `participa_r2`, `ptje_ronda1`, `ptje_ronda2`, `ptje_progra`, `ptje_trabajo`, `ptje_rondas`, `ptje_total`, `turno_competir`) VALUES
(5, 'LaB', 1, 1, 1, 1, 120, 115, 280, 373, 120, 258, 4),
(6, 'ELECTRODINAMIX', 1, 1, 1, 1, 235, 220, 350, 355, 235, 313, 6),
(7, 'Robo-Hots', 1, 1, 1, 1, 55, 45, 230, 351, 55, 212, 15),
(8, 'Robotech', 1, 1, 1, 1, 75, 35, 265, 387, 75, 242, 16),
(9, 'NXT league', 1, 1, 1, 1, 200, 150, 350, 351, 200, 300, 17),
(10, 'STREET NXT', 1, 1, 1, 1, 275, 275, 290, 373, 275, 313, 14),
(11, 'CraftWare', 1, 1, 1, 1, 295, -1, 310, 391, 295, 332, 5),
(12, 'EV3', 1, 1, 1, 1, 55, 35, 250, 337, 55, 214, 8),
(13, 'Alfazul', 0, 1, 1, 1, 145, 45, 290, 351, 145, 262, 2),
(14, 'DsvPlanck', 0, 1, 1, 1, 140, 285, 365, 380, 285, 343, 9),
(15, 'La Roja Robotica', 0, 1, 1, 1, 80, 80, 340, 360, 80, 260, 12),
(16, 'Not Exactly Programmers (NXP)', 0, 1, 1, 1, 75, 95, 320, 373, 95, 263, 3),
(17, 'NX Sen Theta', 0, 1, 1, 1, 255, 295, 370, 315, 295, 327, 1),
(18, 'NXT Brotherhood', 0, 1, 1, 1, 230, 160, 280, 380, 230, 297, 19),
(19, 'RAMbot`s', 0, 1, 1, 1, 55, 270, 350, 364, 270, 328, 18),
(20, 'Robotratas', 0, 1, 1, 1, 75, 35, 220, 380, 75, 225, 11),
(21, 'shílhénhóz', 0, 1, 1, 1, 280, 65, 320, 355, 280, 318, 10),
(22, 'Mante''CiP', 0, 1, 1, 1, 200, 200, 340, 328, 200, 289, 13),
(23, 'ElectroLover''s', 0, 1, 1, 1, 305, 265, 320, 391, 305, 339, 7);

-- --------------------------------------------------------

--
-- Table structure for table `2014-1_talleres`
--

CREATE TABLE IF NOT EXISTS `2014-1_talleres` (
`id` int(11) NOT NULL,
  `nombre` varchar(255) NOT NULL,
  `tiempo` int(11) NOT NULL DEFAULT '0',
  `precision_movimiento` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=20 ;

--
-- Dumping data for table `2014-1_talleres`
--

INSERT INTO `2014-1_talleres` (`id`, `nombre`, `tiempo`, `precision_movimiento`) VALUES
(1, 'Bastián A', 97, 9),
(2, 'Felipe Z', 97, 9),
(3, 'Ivan S', 97, 9),
(4, 'Bárbara R', 132, 8),
(5, 'Bárbara B', 132, 8),
(6, 'Felipe S', 132, 8),
(7, 'Betzabe E', 132, 8),
(8, 'Esteban L', 94, 5),
(9, 'Franco A', 94, 5),
(10, 'Vicente B', 94, 5),
(11, 'Fabricio S', 102, 7),
(12, 'Matias C', 102, 7),
(13, 'Camila V', 102, 7),
(14, 'Camila M', 170, 8),
(15, 'Catalina T', 170, 8),
(16, 'Denisson D', 170, 8),
(17, 'Cristobal L', 200, 9),
(18, 'Sebastián Z', 200, 9),
(19, 'Jean Carlo L', 200, 9);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `2014-1_equipos`
--
ALTER TABLE `2014-1_equipos`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `2014-1_talleres`
--
ALTER TABLE `2014-1_talleres`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `2014-1_equipos`
--
ALTER TABLE `2014-1_equipos`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=24;
--
-- AUTO_INCREMENT for table `2014-1_talleres`
--
ALTER TABLE `2014-1_talleres`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=20;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
