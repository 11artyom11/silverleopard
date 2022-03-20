/**
 * @file io_unit.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This IOModel class is made to handle client input and output 
 * and provide multiprocess mechanism for this process
 * Is defined in iounit namespace
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __IO_UNIT_H__
#define __IO_UNIT_H__

#include <queue>
#include <thread>
#include <mutex>
#include <ostream>
#include <istream>
#include "../../../lib/include/helpers/constants.h"
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"

namespace iounit
{
    class IOModel
    {
        public:
            IOModel();
            ~IOModel();
            template <typename ...mesType>
            void write_q (mesType... istreams);

            template <typename ...mesType>
            void read_q (mesType... messages);

        private:
        /*Queues in which we store output and input streams which 
        will be released in near future*/
            std::queue<std::thread> wrtie_thread_q;
            std::queue<std::thread> read_thread_q;
            std::mutex write_mutex;
            std::mutex read_mutex;

            

    };
}

/*This function works in atomic way*/
template <typename ... mesType>
void iounit::IOModel::write_q(mesType... istreams)
{
    /*Lock mutex to do atomic write to queue and check in 
        empty subject write queue*/
    write_mutex.lock();

    /*From here must be DB manager write functions released*/

    /********************************************/
    /*Think over turning mutexes into semaphores*/
    /********************************************/

    write_mutex.unlock();
}

/*This function works in atomic way*/
template <typename... mesType>
void iounit::IOModel::read_q(mesType... messages)
{

    /*Lock mutex to do atomic read to queue and check in 
        empty subject read queue*/
    read_mutex.lock();
    
    Debug().info(messages...);

    read_mutex.unlock();
}

#endif
