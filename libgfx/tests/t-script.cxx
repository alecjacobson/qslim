/************************************************************************

  Test the libgfx scripting facility.

  by Michael Garland, 2000.
  
  $Id: t-script.cxx,v 1.7 2002/12/20 19:07:03 garland Exp $

 ************************************************************************/

#include <gfx/gfx.h>
#include <gfx/script.h>
#include <gfx/vec3.h>

using namespace std;

// usage: add <x>*
//     Adds all numbers listed on the line and prints the result
// 
// usage: avg <x>*
//     Averages all numbers listed on the line and prints the result
//
int proc_add(const CmdLine &cmd)
{
    std::vector<double> values;
    double sum = 0.0;

    cmd.collect_as_numbers(values);
    std::vector<double>::size_type count;
    for(count=0; count<values.size(); count++)
	sum += values[count];

    if( cmd.opname() == "avg" && count>0 )
	sum /= (double)count;

    cout << sum << endl;
    return SCRIPT_OK;
}

// usage: vec3 <x> <y> <z>
//     Constructs a 3-vector and prints the result
int proc_vec3(const CmdLine &cmd)
{
    if( cmd.argcount() != 3 )  return SCRIPT_ERR_SYNTAX;

    Vec3 v;
    cmd.collect_as_numbers(v, 3);

    cout << v << endl;
    return SCRIPT_OK;
}

// usage: echo <msg>
//     Prints all the text following the command name verbatim
int proc_echo(const CmdLine &cmd)
{
    cout << cmd.argline() << endl;
    return SCRIPT_OK;
}

int main(int argc, char *argv[])
{
    CmdEnv env;

    env.register_command("add", proc_add);
    env.register_command("avg", proc_add);
    env.register_command("echo", proc_echo);
    env.register_command("vec3", proc_vec3);

    for(int i=1; i<argc; i++)
	script_do_file(argv[i], env);

    return 0;
}
