1)

DROP PROCEDURE IF EXISTS zadanie1;

DELIMITER $$

CREATE PROCEDURE zadanie1(
    IN
    _imie varchar(45),
    _nazwisko varchar(45)
)

BEGIN

SELECT
wypozyczenia.id_wypozyczenia,
wypozyczenia.data_wyp,
wypozyczenia.data_zwr,
samochody.nr_rejestracyjny,
samochody.marka,
samochody.model
FROM wypozyczenia
JOIN dane_wypozyczen
ON dane_wypozyczen.id_wypozyczenia = wypozyczenia.id_wypozyczenia
JOIN samochody
ON dane_wypozyczen.id_samochodu = samochody.id_samochodu
JOIN klienci
ON wypozyczenia.id_klienta = klienci.id_klienta
WHERE klienci.imie_klienta = _imie
AND klienci.nazwisko_klienta = _nazwisko;

END$$

DELIMITER ;


2)

DROP PROCEDURE IF EXISTS zadanie2;

DELIMITER $$

CREATE PROCEDURE zadanie2(
    IN
    _start_date date,
    _end_date date
)

BEGIN

SET @max = (
SELECT COUNT(*) v
FROM wypozyczenia
WHERE wypozyczenia.data_wyp > _start_date
AND wypozyczenia.data_zwr < _end_date
GROUP BY wypozyczenia.id_klienta
ORDER BY v
DESC LIMIT 1
);

CREATE TEMPORARY TABLE temp
AS SELECT
klienci.id_klienta,
COUNT(klienci.id_klienta) v
FROM klienci
JOIN wypozyczenia
ON klienci.id_klienta = wypozyczenia.id_klienta
WHERE wypozyczenia.data_wyp > _start_date
AND wypozyczenia.data_zwr < _end_date
GROUP BY klienci.id_klienta
HAVING v = @max;

SELECT
klienci.imie_klienta,
klienci.nazwisko_klienta
FROM klienci
WHERE klienci.id_klienta
IN (SELECT temp.id_klienta FROM temp);

END $$

DELIMITER ;

CALL zadanie2("2022-12-01","2022-12-31");

