/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/04 12:16:08 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	init_data(t_data *data, const char *format)
{
	data->chars_written = 0;
	data->s = format;
	data->buffer = malloc(BUF_SIZE * sizeof(char));
	if (NULL == data->buffer)
		return (MALLOC_ERROR);
	data->buffer_index = 0;
	ft_memset(data->buf, 0, BUF_SIZE * sizeof(char));
	return (OK);
}

int	ft_printf(const char *format, ...)
{
	t_data	data;
	//init data and variadic functions
	va_start (data.ap, format);
	if (init_data(&data))
		return (-1);
	//loop to iterate the string
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (parse_format(&data));
				{
					return (PARSE_ERROR);
				}
			render_format(&data);
		}
		else
		{
			write_buffer(&data, *data.s);
		}
		//pointer arithmetic
		++data.s;
	}
	//write output
	flush_buffer(&data);
	//cleanup functions
	va_end(data.ap);
	free(data.buffer);
	return(data.chars_written);
}
