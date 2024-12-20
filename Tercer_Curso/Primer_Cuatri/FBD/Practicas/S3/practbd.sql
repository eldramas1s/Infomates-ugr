create table pieza(
    codpie VARCHAR2(3) CONSTRAINT codpie_clave_primaria PRIMARY KEY,
    nompie VARCHAR2(20) CONSTRAINT nompie_no_nulo NOT NULL,
    color VARCHAR2(10),
    peso NUMBER(5,2)
    CONSTRAINT peso_entre_0_y_100 CHECK (peso>0 and peso<=100),
    ciudad VARCHAR2(15));
    
select * from pieza;

create table proyecto(
    codpj varchar2(3) constraint codpj_pk primary key,
    nompj varchar2(20) constraint nompj_nn not null,
    ciudad varchar2(15));

select * from proyecto;

create table proveedor(
    codpro varchar2(3) constraint codpro_pk primary key,
    nompro varchar(20) constraint nompro_nn not null,
    status number constraint status_b1y10 check(status between 1 and 10),
    ciudad varchar2(15));
    
select * from proveedor;

create table ventas(
    codpro constraint codpro_ek references proveedor(codpro),
    codpie constraint codpie_ek references pieza (codpie),
    codpj constraint codpj_ek references proyecto(codpj),
    cantidad number(4),
    fecha date,
    constraint ventas_pk primary key (codpro,codpj,codpie));
    
alter table ventas add fecha date;

select * from ventas;

commit;

select peso,codpie from pieza;

delete from pieza where codpie=0;

update pieza set peso = 3.0 where codpie=0;

update pieza set codpie = 000 where color='oro';

commit;

--drop table proyecto;
--drop table ventas;
--delete tables ventas;
--delete tables proveedor;
--delete tables proyecto;
--delete tables pieza;
--Proveedor tuplas

insert into proveedor values ('S1', 'Jose Fernandez', '2', 'Madrid');
insert into proveedor values ('S2', 'Manuel Vidal', '1', 'Londres');
insert into proveedor values ('S3', 'Luisa Gomez', '3', 'Lisboa');
insert into proveedor values ('S4', 'Pedro Sanchez', '4', 'Paris');
insert into proveedor values ('S5', 'Maria Reyes', '5', 'Roma');
insert into proveedor values ('S6', 'Jose Perez', '6', 'Bruselas');
insert into proveedor values ('S7', 'Luisa Martin', '7', 'Atenas');

--Pieza tuplas 
insert into pieza values('P1', 'Tuerca', 'Gris', 2.5 , 'Madrid');
insert into pieza values('P2', 'Tornillo', 'Rojo', 1.25 , 'Paris');
insert into pieza values('P3', 'Arandela', 'Blanco', 3 , 'Londres');
insert into pieza values('P4', 'Clavo', 'Gris', 5, 'Lisboa');
insert into pieza values('P5', 'Alcayata', 'Blanco', 10 , 'Roma');

--Proyecto tuplas
insert into proyecto values('J1', 'Proyecto 1', 'Londres');
insert into proyecto values('J2', 'Proyecto 2', 'Londres');
insert into proyecto values('J3', 'Proyecto 3', 'Paris');
insert into proyecto values('J4', 'Proyecto 4', 'Roma');

--Ventas tuplas 
insert into ventas values('S1', 'P1', 'J1', '150', to_date('18/09/1997', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P1', 'J2', '100', to_date('06/05/1996', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P1', 'J3', '500', to_date('06/05/1996', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P2', 'J1', '200', to_date('22/07/1995', 'dd/mm/yyyy'));
insert into ventas values('S2', 'P2', 'J2', '15', to_date('23/11/2004', 'dd/mm/yyyy'));
insert into ventas values('S4', 'P2', 'J3', '1700', to_date('28/11/2000', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P3', 'J1', '800', to_date('22/07/1995', 'dd/mm/yyyy'));
insert into ventas values('S5', 'P3', 'J2', '30', to_date('01/04/2014', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P4', 'J1', '10', to_date('22/07/1995', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P4', 'J3', '250', to_date('09/03/1994', 'dd/mm/yyyy'));
insert into ventas values('S2', 'P5', 'J2', '300', to_date('23/11/2004', 'dd/mm/yyyy'));
insert into ventas values('S2', 'P2', 'J1', '4500', to_date('15/08/2004', 'dd/mm/yyyy'));
insert into ventas values('S3', 'P1', 'J1', '90', to_date('09/06/2004', 'dd/mm/yyyy'));
insert into ventas values('S3', 'P2', 'J1', '190', to_date('12/04/2002', 'dd/mm/yyyy'));
insert into ventas values('S3', 'P5', 'J3', '20',to_date('28/11/2000', 'dd/mm/yyyy'));
insert into ventas values('S4', 'P5', 'J1', '15', to_date('12/04/2002', 'dd/mm/yyyy'));
insert into ventas values('S4', 'P3', 'J1', '100', to_date('12/04/2002', 'dd/mm/yyyy'));
insert into ventas values('S4', 'P1', 'J3', '1500', to_date('26/01/2003', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P4', 'J4', '290', to_date('09/03/1994', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P2', 'J4', '175', to_date('09/03/1994', 'dd/mm/yyyy'));
insert into ventas values('S5', 'P1', 'J4', '400', to_date('01/04/2014', 'dd/mm/yyyy'));
insert into ventas values('S5', 'P3', 'J3', '400', to_date('01/04/2014', 'dd/mm/yyyy'));
insert into ventas values('S1', 'P5', 'J1', '340', to_date('06/02/2010', 'dd/mm/yyyy'));
insert into ventas values('S6', 'P1', 'J1', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S6', 'P1', 'J2', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S6', 'P1', 'J3', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S6', 'P1', 'J4', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S7', 'P1', 'J1', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S7', 'P1', 'J2', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S7', 'P1', 'J3', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
insert into ventas values('S7', 'P1', 'J4', '340', to_date('10/02/2006', 'dd/mm/yyyy'));
-- Ejercicio 2.4.

insert into ventas values ('S3', 'P1', 'J1', 150, to_date('24/12/05','dd/mm/yy')); -- falla por formato de fecha y por ruptura de condicion de clave externa.

insert into ventas (codpro, codpj) values ('S4', 'J2'); -- falla porque el codigo de pieza no puede ser nulo.

insert into ventas values('S5', 'P3', 'J6',400, to_date('25/12/00','dd/mm/yy')); -- falla porque no esta especificado el formato y en caso de especificarlo fall por ruptura de metarregla de entidad referencial

select * from proyecto;
select * from pieza;
select * from proveedor;
select * from ventas;

-- Ejercicio 2.5.

update ventas set fecha = to_date('2005', 'yyyy') where codpro='S5';

select codpro,codpie, to_char(fecha, '"Dia" day, dd/mm/yy') from ventas;


-- Guardar
COMMIT;

--rollback;

--Capítulo 3


-- Ejemplo 3.1
select ciudad from proyecto;
select * from proyecto;

--Ejemplo 3.2
select * from proveedor;

select codpro, nompro, status, ciudad from proveedor;

--Ejemplo 3.3
select codpro from ventas where codpj='J1';

--Ejercicio 3.1
-- Resultado: Granada dos veces.

--Ejercicio 3.2
select codpro,codpie,codpj from ventas;
select distinct codpro,codpie,codpj from ventas;

-- Ejercicio 3.3
select * from pieza where ciudad = 'Madrid';
select * from pieza where color = 'Rojo' or color = 'Gris';
select * from pieza where (ciudad='Madrid' and (color='Rojo' or color='Gris'));

--Ejercicio 3.4

select * from ventas where cantidad between 200 and 300;

-- Ejercicio 3.5

select * from pieza where nompie like '_ornillo';

-- Ejercicio 3.6

select table_name from ALL_TABLES where table_name like upper('%ventas');

-- Ejercicio 3.7 

select * from proveedor;
select * from pieza;

select  ciudad from proveedor where status >= 2
minus 
select  ciudad from pieza where codpie like 'P1';

select distinct ciudad from proveedor where status > 2 and
ciudad not in (select distinct ciudad from proveedor where status > 2 intersect select distinct ciudad from pieza where codpie = 'P1');

-- Otra forma

select proveedor.ciudad
from proveedor
where proveedor.status>2 
intersect 
select proveedor.ciudad
from proveedor,pieza 
where pieza.codpie = 'P1' and pieza.ciudad != proveedor.ciudad;

-- Ejercicio 3.8

select codpj from ventas where codpro = 'S1'
minus 
select codpj from ventas where codpro != 'S1';


select *from ventas;

-- Ejercicio 3.9

select ciudad from proveedor
union
select ciudad from proyecto
union 
select ciudad from pieza;

-- Ejercicio 3.10

select  ciudad from proveedor
union all 
select  ciudad from proyecto
union all 
select  ciudad from pieza;
-- Salen repetidos

-- Ejercicio 3.11

select * from ventas,proveedor;

commit;
-- 217 tuplas

-- Ejercicio 3.12
with tmp as (select * from ventas where cantidad>30) 
select * from tmp;                                      -- NO HACER

select ventas.codpie,ventas.codpj,ventas.codpro,p1.ciudad 
from ventas,(select codpie,ciudad from pieza) p1,(select codpj,ciudad from proyecto)p2,
(select codpro,ciudad from proveedor)p3 where (ventas.codpie=p1.codpie
and ventas.codpj=p2.codpj and ventas.codpro=p3.codpro and p1.ciudad=p2.ciudad and p2.ciudad=p3.ciudad);

--select * from ventas,(select ciudad from proveedor);


-- Ejercicio 3.13

select s.codpro,p.codpro from proveedor s, proveedor p where s.ciudad>p.ciudad;

-- Ejercicio 3.14

select codpie,peso from pieza
minus
select a.codpie,a.peso from pieza a,pieza b where a.peso<b.peso;


-- Ejercicio 3.15

select s.codpie from ventas s join (select codpro from proveedor where ciudad='Madrid') v on (s.codpro=v.codpro); 
select s.codpie from ventas s natural join(select codpro from proveedor where ciudad='Madrid');

-- Ejercicio 3.16

-- TODO

-- Ejercicio 3.17

select nompro from proveedor; --order by nompro;


--Ejercicio 3.18

select * from ventas order by cantidad , fecha desc;


-- Ejercicio 3.19

select codpie from ventas where codpro in (select codpro from proveedor where ciudad='Madrid');

-- Ejercicio 3.20

select codpj from proyecto where ciudad in (select ciudad from pieza);

-- Ejercicio 3.21

select codpj from proyecto minus select codpj from ventas where codpie in (select codpie from pieza where color='Rojo' and ciudad ='Londres');


-- Ejercicio 3.22

select codpie from pieza where peso > ANY (select peso from pieza where nompie='tornillo');

-- Ejercicio 3.23

select codpie from pieza where peso >= ALL (select peso from pieza);    -- Es muy importante el igual

commit;

select * from ventas;

select * from user_tables;


-- Ejercicio 3.24

select distinct codpie
from ventas
where not exists (
select codpj from proyecto
minus
select codpie from ventas where (proyecto.codpj=ventas.codpj and proyecto.ciudad='Londres'));

select * from ventas where codpj in (select codpj from proyecto where ciudad='Londres');

select codpj from proyecto where ciudad='Londres';

-- Ejercicio 3.26

select count(distinct codpie) from ventas where cantidad > 1000;

-- Ejercicio 3.27

select max(peso) from pieza;
















-- Ejercicio 3.28
SELECT * FROM pieza;

SELECT * 
FROM pieza
WHERE peso = (SELECT MAX(peso) from pieza);

-- Otra forma

SELECT * 
FROM pieza
WHERE peso IN (SELECT MAX(peso) 
                FROM pieza);

-- Otra forma
SELECT p1.*
FROM pieza p1
MINUS
SELECT p2.*
FROM pieza p2,pieza p3 
WHERE (p2.peso < p3.peso);
























-- Ejercicio 3.29 

SELECT codpie, MAX(peso) FROM pieza;








SELECT codpie, SUM(cantidad)
FROM ventas
GROUP BY codpie;

-- Ejercicio 3.36

SELECT codpie, SUM(cantidad)
FROM ventas
GROUP BY codpie
HAVING SUM(cantidad) = (SELECT MAX(SUM(ventas_a.cantidad))
                        FROM ventas ventas_a
                        GROUP BY ventas_a.codpie);

-- Otra forma

SELECT codpie, SUM(cantidad)
FROM ventas
GROUP BY codpie
HAVING SUM(cantidad) IN (SELECT MAX(SUM(ventas_a.cantidad))
                        FROM ventas ventas_a
                        GROUP BY ventas_a.codpie);


-- Ejercicio 5.2 

create table acceso (testigo NUMBER);

insert into acceso values(1);
insert into acceso values(2);

grant select on acceso to x0976938;

revoke select on acceso from x0976938;

grant select on acceso to x0976938 with grant option;



