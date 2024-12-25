-- Ejercicios adicionales

--------------------------------------------------------------------------------
-- Ejercicio 1.7

create table equipos(
    codE varchar(3) constraint codE_pk primary key,
    nombreE varchar(20) unique not null,
    localidad varchar(20) not null,
    entrenador varchar(20) not null,
    fecha_crea date not null
);

create table jugadores(
    codJ varchar(3) primary key,
    codE varchar(3) not null references equipos(codE),
    nombreJ varchar(20) not null);
    
create table encuentros(
    Elocal varchar(20) references equipos(nombreE),
    Evisitante varchar(20) references equipos(nombreE),
    fecha date,
    Plocal number check(Plocal>=0) default 0,
    Pvisitante number check(Pvisitante>=0) default 0,
    primary key(Elocal,Evisitante));
    
create table faltas(
    codJ varchar(3) references jugadores(codJ),
    Elocal varchar(20) references encuentros(Elocal),
    Evisitante varchar(20) references encuentros(Evisitante),
    faltas number check(faltas between 0 and 5) default 0,
    primary key (codJ, Elocal, Evisitante));
    
select * from user_tables;

--------------------------------------------------------------------------------

-- Ejercicio 2.7

insert into equipos values('A','B', 'X', 'Juan',to_date('10/11/2001','dd/mm/yyyy'));
select * from equipos;

--------------------------------------------------------------------------------

-- Ejercicio 3.72

select Elocal
from encuentros 
group by Elocal;

select * from user_tables;