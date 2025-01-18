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


--------------------------------------------------------------------------------
-- Ejercicio 1.1 adaptado
describe ventas;

-- Ejercicio 1.4
create table acceso (testigo NUMBER);
drop table acceso;
delete table acceso;
describe acceso;

-- Ejercicio 1.5

alter table acceso add (fechabaja date);
describe acceso;

-- Ejercicio 1.6 

describe ventas;

--------------------------------------------------------------------------------

-- Ejercicio 2.1 adaptado

select table_name from user_tables where table_name like 'VENTAS';

-- Ejercicio 2.2 comentado
-- update plantilla set nombre='Luis' where dni='12345678':

-- Ejercicio 2.3 comentado
-- delete from plantilla no se el por que

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

-- Ejercicio 2.6
select codpro, codpie, to_char(fecha,'"Dia: " day, dd/mm/yyyy') from ventas;

--Capítulo 3


-- Ejemplo 3.1
select ciudad from proyecto;
select * from proyecto;

--Ejemplo 3.2
select * from proveedor;

select codpro, nompro, status, ciudad from proveedor;

--Ejemplo 3.3
select codpro from ventas where codpj='J1';

-- Ejemplo 3.5
sELECT cantidad/12, round(cantidad/12,3), trunc(cantidad/12,3),
floor(cantidad/12), ceil(cantidad/12)
FROM ventas
WHERE (cantidad/12)>10;

-- floor -> toma la parte entera
-- ceil -> toma la parte entera superior

--Ejercicio 3.1
-- Resultado: Londres dos veces.
select ciudad from proyecto; -- ->
select distinct ciudad from proyecto;

--Ejercicio 3.2
select count(*) from (select codpro,codpie,codpj from ventas);
select count(*) from (select distinct codpro,codpie,codpj from ventas);
-- No es necesario porque lo que estamos proyectando son claves primarias que el conjunto debe ser unico.

-- Ejercicio 3.3

select * from pieza where (ciudad='Madrid' and (color='Rojo' or color='Gris'));

-- Otra forma mas rebuscada

select * from pieza where ciudad like 'Madrid'
intersect
(select * from pieza where color like '_ojo'
union 
select * from pieza where color like '_ris');

--Ejercicio 3.4

select * from ventas where cantidad between 200 and 300 order by cantidad desc;

-- Ejercicio 3.5

select * from pieza where nompie like '_ornillo';

-- Ejercicio 3.6

select distinct table_name from ALL_TABLES where table_name like upper('ventas');

-- Ejercicio 3.7 

select  ciudad from proveedor where status >= 2
minus 
select  ciudad from pieza where codpie like 'P1'; -- No es necesario usar distinct pues es una consulta algebraica

select distinct ciudad from proveedor where status > 2 and
ciudad not in (select distinct ciudad from proveedor where status > 2 intersect select distinct ciudad from pieza where codpie = 'P1');

-- Otra forma 

select distinct ciudad from proveedor where status > 2 and
not exists (select distinct ciudad from proveedor where status > 2 intersect select distinct ciudad from pieza where codpie = 'P1');
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

select codpj from ventas where codpro like 'S1' and not exists (select * from ventas where codpro != 'S1');

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


-- Ejercicio 3.13

select s.codpro,p.codpro from proveedor s, proveedor p where s.ciudad>p.ciudad;

-- Ejercicio 3.14

select codpie,peso from pieza
minus
select a.codpie,a.peso from pieza a,pieza b where a.peso<b.peso;

select codpie, peso from pieza where peso = (select max(peso) from pieza);
select codpie, peso from pieza where peso >= all (select peso from pieza);
select codpie, peso from pieza where peso in (select max(peso) from pieza);
-- Ejercicio 3.15

select s.codpie from ventas s join (select codpro from proveedor where ciudad='Madrid') v on (s.codpro=v.codpro); 
select s.codpie from ventas s natural join(select codpro from proveedor where ciudad='Madrid');

-- Ejercicio 3.16

select ciudad, codpie from (ventas natural join( select codpj, ciudad from proyecto)) natural join (select ciudad, codpro from proveedor);
select ciudad, codpie from ventas natural join ( select codpj,codpro,ciudad from proyecto natural join (select ciudad,codpro from proveedor));
select r.ciudad, ventas.codpie from ventas join (select p.codpj,q.codpro,ciudad from proyecto p join (select codpro,ciudad from proveedor) q on (p.ciudad = q.ciudad)) r on ( ventas.codpro=r.codpro and ventas.codpj = r.codpj);

-- Ejercicio 3.17

select nompro from proveedor; --order by nompro;


--Ejercicio 3.18

select * from ventas order by cantidad , fecha desc, codpro asc;


-- Ejercicio 3.19

select codpie from ventas where codpro in (select codpro from proveedor where ciudad='Madrid');

-- Ejercicio 3.20

select codpj from proyecto where ciudad in (select ciudad from pieza);

-- Ejercicio 3.21

select codpj from proyecto minus select codpj from ventas where codpie in (select codpie from pieza where color='Rojo' and ciudad ='Londres');


-- Ejercicio 3.22

select codpie from pieza where peso > ANY (select peso from pieza where nompie='tornillo');
select codpie from pieza p where not exists (select peso from pieza q where nompie = 'tornillo' and p.peso <= q.peso);

-- Ejercicio 3.23

select codpie from pieza where peso >= ALL (select peso from pieza);    -- Es muy importante el igual

commit;

select * from ventas;

select * from user_tables;


-- Ejercicio 3.24(division)

select codpie 
from pieza
where not exists( select codpj from proyecto where ciudad like 'Londres'
                  minus 
                  select codpj from ventas where ventas.codpie = pieza.codpie);
                  
select codpie 
from pieza 
where not exists( select codpj 
                  from proyecto 
                  where ciudad like 'Londres' and not exists (select * 
                                                             from ventas 
                                                             where ventas.codpie=pieza.codpie and ventas.codpj = proyecto.codpj));

select codpie
from pieza
minus
select codpie 
from (select s.codpie,p.codpj 
      from (select codpie 
            from pieza) s, (select codpj 
                            from proyecto 
                            where ciudad like 'Londres') p
      minus
      select codpie,codpj 
      from ventas);
      
select * from ventas;

-- Ejercicio 3.25(division)

select codpro 
from proveedor
where not exists(select codpie from pieza where pieza.ciudad in (select ciudad from proyecto)
                 minus 
                 select codpie from ventas where ventas.codpro=proveedor.codpro);
                 
select codpro
from proveedor 
where not exists( select codpie 
                  from pieza 
                  where pieza.ciudad in (select ciudad from proyecto) 
                  and not exists(select * 
                                 from ventas 
                                 where ventas.codpie=pieza.codpie
                                 and proveedor.codpro=ventas.codpro));

select codpro
from proveedor
minus 
select codpro from (select s.codpro,p.codpie from (select codpro from proveedor)s, (select codpie from pieza where pieza.ciudad in (select ciudad from proyecto))p
                    minus
                    select codpro,codpie from ventas);
                    
-- Ejercicio 3.26

select count(distinct codpie) from ventas where cantidad > 1000; -- Sin el distinct considera dos veces la misma pieza

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


-- Ejercicio 3.30

select distinct v2.codpro
from ventas v2,ventas v3, ventas v4
where (v2.codpro=v3.codpro) and (v3.codpro = v4.codpro) 
      and (v2.codpie!=v3.codpie or v2.codpj != v3.codpj)
      and (v3.codpie != v4.codpie or v3.codpj != v4.codpj)
      and (v3.codpie != v4.codpie or v2.codpj != v4.codpj); -- Deberia extenderse para 4 o mas pero es un toston
      
describe ventas;
select * from ventas;


select codpro 
from (select codpro, count(cantidad) a
      from ventas
      group by codpro)
where a>3;

select codpro, count(cantidad) a
      from ventas
      group by codpro
      having a>3;   -- Esto no nos deja

-- Ejercicio 3.31

select codpie,nompie,avg(cantidad)
from ventas natural join (select codpie, nompie from pieza)
group by codpie,nompie
order by codpie;

SELECT nompro, cantidad
FROM proveedor NATURAL JOIN (SELECT * FROM ventas WHERE cantidad>800);
-- Ejercicio 3.32

select codpro, avg(cantidad)
from ventas 
where codpie like 'P1'
group by codpro;

-- Ejercicio 3.33

select codpie,codpro, sum(cantidad)
from ventas
group by codpie,codpro;

-- Ejercicio 3.34

select v.codpro, v.codpj , j.nompj, avg(cantidad)
from ventas v, proyecto j
where v.codpj=j.codpj
group by v.codpj, j.nompj, v.codpro;

-- Ejercicio 3.35

describe proveedor;

select nompro,sum(cantidad)
from ventas natural join (select codpro,nompro from proveedor)
group by codpro,nompro
having sum(cantidad)>1000;

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

-- Ejercicio 3.37 

SELECT *
FROM ventas
WHERE fecha BETWEEN TO_DATE('01/01/2002', 'DD/MM/YYYY')
AND TO_DATE('31/12/2004', 'DD/MM/YYYY')
order by fecha;

SELECT *
FROM ventas
WHERE fecha BETWEEN to_char(fecha, 'DD/MM/YYYY')
AND to_char(fecha, 'DD/MM/YYYY');


-- Ejercicio 3.38
select to_char(fecha, 'mm'), avg(cantidad) 
from ventas
group by to_char(fecha, 'mm')
order by to_char(fecha,'mm');

describe dictionary;
-- Ejercicio 3.39

-- Ejercicio 3.40

-- Ejercicio 3.41

-- Ejercicio 3.42
select sum(cantidad) from ventas where codpro like 'S1';

select codpro,sum(cantidad)
from ventas v 
group by codpro
having sum(cantidad) > (select sum(cantidad) from ventas b where b.codpro like 'S1');

-- Ejercicio 3.43
select codpro, sum(cantidad) 
from ventas 
group by codproselect codpie from pieza 
where not exists( select codpj from proyecto 
                  where ciudad='Paris' and not exists (select * from ventas where ventas.codpie = pieza.codpie and ventas.codpj=proyecto.codpj));
having sum(cantidad)= (select max(sum(v1.cantidad)) from ventas v1 group by v1.codpro);

-- Ejercicio 3.44
                  
select codpro
from proveedor
where not exists (select ciudad
                  from proyecto
                  where codpj='S3'
                  minus
                  select distinct ciudad 
                  from ventas natural join (select * from proyecto)
                  where codpj='S3' and ventas.codpro = proveedor.codpro); 

select codpro
from proveedor 
where not exists(select ciudad 
                 from proyecto
                 where codpj='S3' and not exists (select * 
                                                  from (ventas natural join (select * from proyecto)p
                                                   where p.ciudad=proyecto.ciudad and p.codpro = proveedor.codpro));   
-- Ejercicio 3.45

select codpro, count (*)
from ventas 
group by codpro 
having count(codpro)>=10;

-- Ejercicio 3.46

select codpro 
from proveedor
where not exists( select codpie
                  from ventas
                  where codpro ='S1'
                  minus 
                  select codpie 
                  from ventas v 
                  where v.codpro=proveedor.codpro);

select codpro
from proveedor
where not exists( select codpie 
                  from ventas b
                  where codpro = 'S1' and not exists( select *
                                                      from ventas v
                                                      where v.codpie=b.codpie and v.codpro = proveedor.codpro));
                                                
select codpro 
from proveedor
minus
select codpro 
from (select p.codpro, q.codpie 
      from proveedor p, (select * from ventas where codpro = 'S1') q
      minus
      select codpro, codpie from ventas v where p.codpro=v.codpro and q.codpie=v.codpie);

-- Ejercciio 3.47
select codpro, sum(cantidad)
from ventas a
where codpro in (select codpro 
                 from proveedor
                 where not exists(select codpie
                                  from ventas v
                                  where v.codpro = 'S1' and not exists(select * 
                                                                       from ventas b
                                                                       where a.codpro = b.codpro and v.codpie=b.codpie)))
group by codpro;

-- Ejercicio 3.48

select codpj 
from proyecto 
where not exists( select codpro
                  from ventas b
                  where b.codpie='P3' and not exists(select * 
                                                     from ventas v
                                                     where v.codpj = proyecto.codpj and b.codpro =v.codpro));

-- Ejercicio 3.49
select codpro, avg(cantidad)
from ventas
where codpie like '_3'
group by codpro;

-- Ejercicio 3.50
describe user_indexes;

select index_name, table_name, table_owner from user_indexes;
-- Ejercicio 3.51



-- Ejercicio 3.52
select codpro, avg(cantidad)
from proveedor natural join ventas
group by codpro;                -- SI hay un proveedor que no suministra nada no lo obtiene

-- Ejercicio 3.53

select distinct codpro
from ventas
where codpie in (select codpie from pieza where color like 'Rojo');

-- Ejercicio 3.54

select codpro
from proveedor
where not exists( select codpie 
                  from pieza 
                  where color like 'Rojo' and not exists (select * 
                                                          from ventas
                                                          where ventas.codpro = proveedor.codpro and ventas.codpie=pieza.codpie));

-- Ejercicio 3.55

select distinct codpro
from ventas b
where not exists ( select  * from ventas v where v.codpie in (select codpie from pieza where color!='Rojo') and v.codpro=b.codpro)
order by codpro asc;

-- Ejercicio 3.56
select codpro, count(codpie)
from(select codpro,codpie
    from ventas 
    where codpie in (select codpie from pieza where color like 'Rojo'))
group by codpro 
having count(codpie)>1;

-- Ejercicio 3.57

select distinct codpro, v.cantidad from ventas v natural join (select codpro
from proveedor
where not exists( select codpie 
                  from pieza
                  where color='Rojo' and not exists( select * 
                                                     from ventas b
                                                     where b.codpie=pieza.codpie and b.codpro=proveedor.codpro)))
where cantidad > 10
order by codpro;

-- Ejercicio 3.58

update proveedor
    set status=1
    where proveedor.codpro in (select codpro from ventas where not exists (select * from ventas where codpie != 'P1'));

-- Ejercicio 3.59
-- DA pereza hacerlo

commit;

--------------------------------------------------------------------------------

-- Ejercicio 4.1
create view ProveedorLondres as 
select * from proveedor
where ciudad = 'Londres';

insert into ProveedorLondres values('S8', 'Jose Suarez', 3, 'Granada');

select * from ProveedorLondres;

-- Si que se inserta en proveedor pero no en la vista creada

-- Ejercicio 4.2
create view SimpleView as 
select nompro,ciudad from proveedor;

-- La existencia de duplicados por no haber clave primaria no se sabria de que proveedor es acda tupla, asique actualizar seria muy engorroso.

-- Ejercicio 4.3
create view Comview as 
select codpro, nompro, codpj 
from (ventas natural join proveedor)   
where codpie in (select codpie from pieza where color like 'Gris');  

select * from Comview;

-- Insertar aqui es ambiguo pues no se sabe en que tabla hay que insertar asicomo la pieza que se vende en ventas luego la clave primaria incumpliria la metarregla de integridad.

--------------------------------------------------------------------------------í

-- Ejercicio 5.1

describe user_tables;

-- Ejercicio 5.2 

create table acceso (testigo NUMBER);

insert into acceso values(1);
insert into acceso values(2);

grant select on acceso to x0976938;

revoke select on acceso from x0976938;

grant select on acceso to x0976938 with grant option;


--------------------------------------------------------------------------------

-- Consultas sobre el catalogo

select * from all_users;
describe all_users;

describe dictionary;
select * from dictionary where table_name like upper('%index%');
select * from dictionary;

describe all_views;
select view_name from all_views;

select * from user_constraints;
select * from user_cons_columns;

--------------------------------------------------------------------------------

-- Relacion AR 2

-- Ejercicio 1

select distinct c.ciudad, d.ciudad 
from proveedor c ,proyecto d
where exists ( select * 
               from ventas 
               where ventas.codpro=c.codpro and ventas.codpj=d.codpj);
               
-- Ejercicio 2

select codpie 
from ventas v
where exists (select * from ((ventas natural join proveedor natural join proyecto) d where d.codpie = v.codpie));

-- Ejercicio 3

select codpj
from proyecto 
where exists (select codpro from proveedor where proveedor.ciudad = proyecto.ciudad);

-- Ejercicio 4

select distinct c.ciudad, d.ciudad from pieza c,proyecto d;

select ciudad from pieza 
union 
select ciudad from proyecto;

-- Ejercicio 5

select distinct ciudad from proveedor
where not exists (select ciudad from proyecto where proveedor.ciudad = proyecto.ciudad);

-- Ejercicio 6

select ciudad from proveedor 
where exists ( select ciudad from pieza where pieza.ciudad = proveedor.ciudad);

-- Ejercicio 7

select distinct codpj from ventas where codpie in ( select codpie from ventas where codpro like 'S1');

-- Ejercicio 8

select min(cantidad) from ventas;

select cantidad from ventas where cantidad <= ALL (select cantidad from ventas);

select cantidad from ventas 
minus
select a.cantidad from ventas a, ventas b where a.cantidad > b.cantidad;

select cantidad from ventas 
minus
select a.cantidad from ventas a join ventas b on (a.cantidad > b.cantidad);

-- Ejercicio 9

select distinct codpj from ventas
where codpie not in (select codpie from pieza where color like 'rojo') and codpro not in( select codpro from proveedor where ciudad like 'Londres');

-- Ejercicio 10

select codpj from proyecto 
where not exists(select * from ventas where ventas.codpj = proyecto.codpj and ventas.codpro!='S1');

select codpj from ventas 
where codpro = 'S1'
minus 
select codpj from ventas 
where codpro != 'S1';

-- Ejercicio 11

select codpie from pieza 
where not exists( select codpj from proyecto 
                  where ciudad='Paris' and not exists (select * from ventas where ventas.codpie = pieza.codpie and ventas.codpj=proyecto.codpj));
                  
select codpie from pieza 
where not exists( select codpj from proyecto p where ciudad='Paris' 
                  minus 
                  select codpj from ventas where p.codpj=ventas.codpj and ventas.codpie=pieza.codpie);
                  
select codpie from pieza 
minus 
select codpie from (select codpie,codpj from pieza,proyecto where proyecto.ciudad='Paris'
                    minus
                    select codpie,codpj from ventas);
                    
-- Ejercicio 12

select codpro from proveedor
minus 
select v.codpro from ventas v join ventas b on b.codpie!=v.codpie;

-- Ejercicio 13

select codpj from proyecto b
where  not exists ( select codpie from pieza where not exists (select * from ventas v where v.codpie = pieza.codpie and v.codpj=b.codpj and codpro='S1'));

select codpj from ventas b
where not exists(select codpie from pieza minus select codpie from ventas v where v.codpie = pieza.codpie and v.codpj = b.codpj);

-- Ejercicio 14

select codpro from proveedor p
where not exists(select codpie,codpj from pieza a, proyecto c where not exists (select codpie,codpj from ventas v where (a.codpie=v.codpie and c.codpj=v.codpj and p.codpro=v.codpro)));

-- Ejercicio 15
select codpie,peso from pieza where peso in (select max(peso) from pieza having max(peso)<100 );

-- Ejerccio 16

select codpj from ventas where codpj in (select codpj from proyecto where ciudad like 'Jaen') and codpie in (select codpie from pieza where peso >= ALL(select peso from pieza));

-- Ejercicio 17

select codpj from ventas 
group by codpj 
having count(codpie)>=2;

-- Ejercicio 18

select codpj from ventas 
group by codpj 
having count(codpie)=2;

-- Ejercicio 19

select codpro from ventas 
group by codpro
having count(*) between 1 and 2;

-- Ejercicio 20

select codpro from proveedor
where not exists (select codpie from pieza where color='rojo' or ciudad='Granada' and not exists( select * from ventas where ventas.codpie=pieza.codpie and ventas.codpro=proveedor.codpro));
