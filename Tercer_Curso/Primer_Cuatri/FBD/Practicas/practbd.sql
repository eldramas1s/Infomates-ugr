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
    codpj constraint codpj_ek references proyecto(codpj),
    codpie constraint codpie_ek references pieza(codpie),
    cantidad number(4),
    constraint ventas_pk primary key (codpro,codpj,codpie));
    
alter table ventas add fecha date;

select * from ventas;

commit;

insert into pieza values (000,'tx1', 'plata', 00000.30, 'Granada');
insert into pieza values (001,'tx1', 'oro', 00000.10, 'Granada');

select peso,codpie from pieza;

delete from pieza where codpie=0;

update pieza set peso = 3.0 where codpie=0;

update pieza set codpie = 000 where color='oro';

commit;

-- Pre ejercicios

insert into proveedor values ( 'S5', 'Juan', 2, null);
insert into pieza values ('P3', 'tornillo', 'plata', 3, 'Granada');
insert into proyecto values ('J6', 'ayunta', 'Granada');


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
