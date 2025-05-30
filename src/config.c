#include "config.h"


static void error(const char* msg, const char* msg1)
{
    fprintf(stderr, "ERROR: %s%s\n", msg, msg1?msg1:"");
    exit(1);
}

Main* read_config() {
    FILE* fp;
    char errbuf[200];

    fp = fopen("../gremlin.toml", "r");
    if (!fp) {
        error("Cannot open gremlin.toml - ", strerror(errno));
    }

    toml_table_t* conf = toml_parse_file(fp, errbuf, sizeof(errbuf));
    fclose(fp);

    if (!conf) {
        error("Cannot parse - ", errbuf);
    }

    Main* main = malloc(sizeof(Main));
    if (!main) {
        error("Failed to allocate memory for main config", NULL);
    }

    toml_table_t* gremlin_table = toml_table_in(conf, "gremlin");
    if (!gremlin_table) {
        error("Missing [gremlin] in toml file...", NULL);
    }

    toml_datum_t enabled = toml_bool_in(gremlin_table, "enabled");
    if (!enabled.ok) {
        error("Missing enabled field in [gremlin]...", NULL);
    }
    main->gremlin.enabled = enabled.u.b;

    toml_datum_t is_scheduled = toml_bool_in(gremlin_table, "is_scheduled");
    if (!is_scheduled.ok) {
        error("Missing is_scheduled field in [gremlin]...", NULL);
    }
    main->gremlin.is_scheduled = is_scheduled.u.b;

    toml_datum_t is_safe = toml_bool_in(gremlin_table, "is_safe");
    if (!is_safe.ok) {
        error("Missing is_safe field in [gremlin]...", NULL);
    }
    main->gremlin.is_safe = is_safe.u.b;

    toml_datum_t level = toml_string_in(gremlin_table, "level");
    if (!level.ok) {
        error("Missing level field in [gremlin]...", NULL);
    }
    main->gremlin.level = strdup(level.u.s);
    free(level.u.s);

    toml_datum_t crontab = toml_string_in(gremlin_table, "crontab");
    if (!crontab.ok) {
        printf("Warning: Missing crontab in [gremlin], assuming you meant to leave it without a cron job...\n");
        main->gremlin.crontab = NULL;
    } else {
        main->gremlin.crontab = strdup(crontab.u.s);
        free(crontab.u.s);
    }

    toml_table_t* db_table = toml_table_in(conf, "database");
    if (!db_table) {
        error("Missing [database] in toml file...", NULL);
    }

    toml_datum_t db_host = toml_string_in(db_table, "host");
    if (!db_host.ok) {
        error("Missing host field in [database]...", NULL);
    }
    main->database.host = strdup(db_host.u.s);
    free(db_host.u.s);

    toml_datum_t db_name = toml_string_in(db_table, "name");
    if (!db_name.ok) {
        error("Missing name field in [database]...", NULL);
    }
    main->database.name = strdup(db_name.u.s);
    free(db_name.u.s);

    toml_datum_t db_user = toml_string_in(db_table, "user");
    if (!db_user.ok) {
        error("Missing user field in [database]...", NULL);
    }
    main->database.user = strdup(db_user.u.s);
    free(db_user.u.s);

    toml_datum_t db_password = toml_string_in(db_table, "password");
    if (!db_password.ok) {
        error("Missing password field in [database]...", NULL);
    }
    main->database.password = strdup(db_password.u.s);
    free(db_password.u.s);

    toml_datum_t db_level = toml_string_in(db_table, "level");
    if (!db_level.ok) {
        error("Missing level field in [database]...", NULL);
    }
    main->database.level = strdup(db_level.u.s);
    free(db_level.u.s);

    toml_table_t* machine_table = toml_table_in(conf, "machine");
    if (!machine_table) {
        error("Missing [machine] in toml file...", NULL);
    }

    toml_datum_t machine_ip = toml_string_in(machine_table, "ip");
    if (!machine_ip.ok) {
        error("Missing ip field in [machine]...", NULL);
    }
    main->machine.ip = strdup(machine_ip.u.s);
    free(machine_ip.u.s);

    toml_datum_t machine_user = toml_string_in(machine_table, "user");
    if (!machine_user.ok) {
        error("Missing user field in [machine]...", NULL);
    }
    main->machine.user = strdup(machine_user.u.s);
    free(machine_user.u.s);

    toml_datum_t machine_password = toml_string_in(machine_table, "password");
    if (!machine_password.ok) {
        error("Missing password field in [machine]...", NULL);
    }
    main->machine.password = strdup(machine_password.u.s);
    free(machine_password.u.s);

    toml_datum_t machine_docker = toml_bool_in(machine_table, "docker");
    if (!machine_docker.ok) {
        error("Missing docker field in [machine]...", NULL);
    }
    main->machine.docker = machine_docker.u.b;

    toml_datum_t machine_level = toml_string_in(machine_table, "level");
    if (!machine_level.ok) {
        error("Missing level field in [machine]...", NULL);
    }
    main->machine.level = strdup(machine_level.u.s);
    free(machine_level.u.s);

    toml_free(conf);
    return main;
}